package travel.model;

import lombok.Data;
import java.math.BigDecimal;
import java.time.LocalDate;

@Data
public class TourOrder {
    private String orderId;
    private String tourId;
    private String applicantName;
    private String contactPhone;
    private int adultCount;
    private int childCount;
    private LocalDate createDate;
    private OrderStatus status;
    private BigDecimal depositAmount;
    private BigDecimal totalAmount;
}