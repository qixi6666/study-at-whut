package travel.service;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.datatype.jsr310.JavaTimeModule;
import travel.model.TourGroup;
import travel.model.TourOrder;
import org.springframework.stereotype.Service;  // 添加这行导入

import java.io.File;
import java.io.IOException;
import java.util.*;

@Service  // 添加这行注解
public class LocalFileDataService {
    private static final String TOURS_FILE = "data/tours.json";
    private static final String ORDERS_FILE = "data/orders.json";
    public final ObjectMapper objectMapper = new ObjectMapper()
        .registerModule(new JavaTimeModule());

    public List<TourGroup> loadAllTourGroups() throws IOException {
        File file = new File(TOURS_FILE);
        if (!file.exists()) {
            return new ArrayList<>();
        }
        return Arrays.asList(objectMapper.readValue(file, TourGroup[].class));
    }

    public void saveAllTourGroups(List<TourGroup> tours) throws IOException {
        File file = new File(TOURS_FILE);
        objectMapper.writerWithDefaultPrettyPrinter().writeValue(file, tours);  // 使用美化输出
    }

    public void saveAllOrders(List<TourOrder> orders) throws IOException {
        File file = new File(ORDERS_FILE);
        objectMapper.writerWithDefaultPrettyPrinter().writeValue(file, orders);  // 使用美化输出
    }

    public List<TourOrder> loadAllOrders() throws IOException {
        File file = new File(ORDERS_FILE);
        if (!file.exists()) {
            return new ArrayList<>();
        }
        return Arrays.asList(objectMapper.readValue(file, TourOrder[].class));
    }
}