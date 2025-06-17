package travel.service;

import java.math.BigDecimal;
import java.util.List;
import travel.model.TourGroup;
import travel.model.TourOrder;  // 添加这行导入语句

public interface TourService {
    TourGroup getTourGroupById(String tourId);
    boolean validateTourGroupEligibility(String tourId, int adultCount, int childCount);
    BigDecimal calculateDeposit(String tourId, int adultCount, int childCount);
    String createTourOrder(String tourId, String applicantName, 
                         String contactPhone, int adultCount, int childCount);
    BigDecimal cancelTourOrder(String orderId);
    List<TourGroup> getAllTourGroups();
    TourOrder getOrderById(String orderId);  // 添加这行方法声明
}