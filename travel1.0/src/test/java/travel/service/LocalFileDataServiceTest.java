package travel.service;

import org.junit.jupiter.api.*;
import travel.model.OrderStatus;
import travel.model.TourGroup;
import travel.model.TourOrder;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

class LocalFileDataServiceTest {
    private LocalFileDataService service;
    private Path tempDir;
    private File testToursFile;
    private File testOrdersFile;

    @BeforeEach
    void setUp() throws IOException {
        tempDir = Files.createTempDirectory("travel-test");
        testToursFile = tempDir.resolve("tours.json").toFile();
        testOrdersFile = tempDir.resolve("orders.json").toFile();
        
        service = new LocalFileDataService() {
            @Override
            public List<TourGroup> loadAllTourGroups() throws IOException {
                File file = testToursFile;
                if (!file.exists()) {
                    return new ArrayList<>();
                }
                return Arrays.asList(objectMapper.readValue(file, TourGroup[].class));
            }

            @Override
            public void saveAllTourGroups(List<TourGroup> tours) throws IOException {
                objectMapper.writerWithDefaultPrettyPrinter().writeValue(testToursFile, tours);
            }

            @Override
            public List<TourOrder> loadAllOrders() throws IOException {
                File file = testOrdersFile;
                if (!file.exists()) {
                    return new ArrayList<>();
                }
                return Arrays.asList(objectMapper.readValue(file, TourOrder[].class));
            }

            @Override
            public void saveAllOrders(List<TourOrder> orders) throws IOException {
                objectMapper.writerWithDefaultPrettyPrinter().writeValue(testOrdersFile, orders);
            }
        };
    }

    @AfterEach
    void tearDown() throws IOException {
        Files.deleteIfExists(testToursFile.toPath());
        Files.deleteIfExists(testOrdersFile.toPath());
        Files.deleteIfExists(tempDir);
    }

    @Test
    void saveAndLoadTourGroups_ShouldWorkCorrectly() throws IOException {
        // 准备测试数据
        TourGroup tour = new TourGroup();
        tour.setTourId("TG001");
        tour.setDepartureDate(LocalDate.now().plusDays(10));
        tour.setDeadline(LocalDate.now().plusDays(5));
        tour.setMaxParticipants(20);
        tour.setCurrentParticipants(0);
    
        List<TourGroup> expected = Arrays.asList(tour);
    
        // 执行保存和加载
        service.saveAllTourGroups(expected);
        List<TourGroup> actual = service.loadAllTourGroups();
    
        // 验证结果
        assertEquals(1, actual.size());
        assertEquals(expected.get(0).getTourId(), actual.get(0).getTourId());
        assertEquals(expected.get(0).getMaxParticipants(), actual.get(0).getMaxParticipants());
    }

    @Test
    void saveAndLoadOrders_ShouldWorkCorrectly() throws IOException {
        // 准备测试数据
        TourOrder order = new TourOrder();
        order.setOrderId("ORDER001");
        order.setTourId("TG001");
        order.setApplicantName("张三");
        order.setContactPhone("13800138000");
        order.setAdultCount(2);
        order.setChildCount(1);
        order.setCreateDate(LocalDate.now());
        order.setStatus(OrderStatus.PENDING);
    
        List<TourOrder> expected = Arrays.asList(order);
    
        // 执行保存和加载
        service.saveAllOrders(expected);
        List<TourOrder> actual = service.loadAllOrders();
    
        // 验证结果
        assertEquals(1, actual.size());
        assertEquals(expected.get(0).getOrderId(), actual.get(0).getOrderId());
        assertEquals(expected.get(0).getApplicantName(), actual.get(0).getApplicantName());
    }
}