package travel.service;

import travel.model.TourGroup;
import travel.model.TourOrder;
import travel.model.OrderStatus;
import org.springframework.stereotype.Service;
import java.io.IOException;  // 添加这行导入语句
import java.util.List;  
import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.UUID;

@Service
public class TourServiceImpl implements TourService {
    private final LocalFileDataService dataService;
    private final Map<String, TourGroup> tourGroups = new HashMap<>();
    private final Map<String, TourOrder> orders = new HashMap<>();

    public TourServiceImpl(LocalFileDataService dataService) {
        this.dataService = dataService;
        try {
            // 初始化时从文件加载数据
            List<TourGroup> loadedTours = dataService.loadAllTourGroups();
            loadedTours.forEach(tour -> tourGroups.put(tour.getTourId(), tour));
            
            List<TourOrder> loadedOrders = dataService.loadAllOrders();
            loadedOrders.forEach(order -> orders.put(order.getOrderId(), order));
        } catch (IOException e) {
            // Log the error and initialize with empty collections
            System.err.println("Failed to load initial data: " + e.getMessage());
            tourGroups.clear();
            orders.clear();
        }
    }

    @Override
    public boolean validateTourGroupEligibility(String tourId, int adultCount, int childCount) {
        TourGroup tour = getTourGroupById(tourId);
        LocalDate now = LocalDate.now();
        
        boolean isBeforeDeadline = now.isBefore(tour.getDeadline());
        boolean hasAvailableSeats = tour.getCurrentParticipants() + adultCount + childCount <= tour.getMaxParticipants();
        
        return isBeforeDeadline && hasAvailableSeats;
    }

    @Override
    public BigDecimal calculateDeposit(String tourId, int adultCount, int childCount) {
        TourGroup tour = getTourGroupById(tourId);
        BigDecimal totalPrice = tour.getPricePerAdult().multiply(BigDecimal.valueOf(adultCount))
                .add(tour.getPricePerChild().multiply(BigDecimal.valueOf(childCount)));
        
        long daysUntilDeparture = ChronoUnit.DAYS.between(LocalDate.now(), tour.getDepartureDate());
        
        if (daysUntilDeparture >= 30) {
            return totalPrice.multiply(BigDecimal.valueOf(0.1));
        } else if (daysUntilDeparture >= 15) {
            return totalPrice.multiply(BigDecimal.valueOf(0.2));
        } else {
            return totalPrice;
        }
    }

    @Override
    public String createTourOrder(String tourId, String applicantName, String contactPhone, 
                                int adultCount, int childCount) {
        TourGroup tour = getTourGroupById(tourId);
        if (!validateTourGroupEligibility(tourId, adultCount, childCount)) {
            throw new IllegalStateException(String.format(
                "无法预订：%s（当前名额：%d/%d，截止日期：%s）",
                tour.getCurrentParticipants() + adultCount + childCount > tour.getMaxParticipants() 
                    ? "名额不足" : "已过截止日期",
                tour.getCurrentParticipants(),
                tour.getMaxParticipants(),
                tour.getDeadline()
            ));
        }
        
        BigDecimal deposit = calculateDeposit(tourId, adultCount, childCount);
        TourOrder order = new TourOrder();
        String orderId = UUID.randomUUID().toString();
        
        order.setOrderId(orderId);
        order.setTourId(tourId);
        order.setApplicantName(applicantName);
        order.setContactPhone(contactPhone);
        order.setAdultCount(adultCount);
        order.setChildCount(childCount);
        order.setCreateDate(LocalDate.now());
        order.setStatus(OrderStatus.PENDING);
        order.setDepositAmount(deposit);
        order.setTotalAmount(calculateTotalPrice(tourId, adultCount, childCount));
        
        // 更新旅游团当前人数
        // 删除这行重复定义
        // TourGroup tour = tourGroups.get(tourId);
        
        // 直接使用前面已经定义的tour变量
        tour.setCurrentParticipants(tour.getCurrentParticipants() + adultCount + childCount);
        
        orders.put(orderId, order);
        try {
            dataService.saveAllOrders(new ArrayList<>(orders.values()));
            dataService.saveAllTourGroups(new ArrayList<>(tourGroups.values()));  // 新增这行
        } catch (IOException e) {
            System.err.println("保存数据失败: " + e.getMessage());
        }
        return orderId;
    }

    @Override
    public BigDecimal cancelTourOrder(String orderId) {
        TourOrder order = getOrderById(orderId);
        if(order == null) {
            throw new IllegalArgumentException("订单不存在");
        }
        order.setStatus(OrderStatus.CANCELLED);  // 修改为两个L
        
        // 恢复旅游团名额
        TourGroup tour = tourGroups.get(order.getTourId());
        tour.setCurrentParticipants(tour.getCurrentParticipants() - 
                             (order.getAdultCount() + order.getChildCount()));
        
        try {
            dataService.saveAllOrders(new ArrayList<>(orders.values()));
            dataService.saveAllTourGroups(new ArrayList<>(tourGroups.values()));  // 新增这行
        } catch (IOException e) {
            System.err.println("保存数据失败: " + e.getMessage());
        }
        return order.getDepositAmount();
    }
    
    private BigDecimal calculateTotalPrice(String tourId, int adultCount, int childCount) {
        TourGroup tour = getTourGroupById(tourId);
        return tour.getPricePerAdult().multiply(BigDecimal.valueOf(adultCount))
                .add(tour.getPricePerChild().multiply(BigDecimal.valueOf(childCount)));
    }

    @Override
    public TourGroup getTourGroupById(String tourId) {
        return tourGroups.get(tourId);
    }
    
    public TourOrder getOrderById(String orderId) {
        return orders.get(orderId);
    }
    
    @Override
    public List<TourGroup> getAllTourGroups() {
        return new ArrayList<>(tourGroups.values());
    }
}