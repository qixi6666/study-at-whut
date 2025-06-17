package travel.model;

import java.math.BigDecimal;
import java.time.LocalDate;

public class TourGroup {
    private String tourId;
    private LocalDate departureDate;
    private LocalDate deadline;
    private int maxParticipants;
    private int currentParticipants;
    private BigDecimal pricePerAdult;
    private BigDecimal pricePerChild;

    // Getters and Setters
    public String getTourId() {
        return tourId;
    }

    public void setTourId(String tourId) {
        this.tourId = tourId;
    }

    public LocalDate getDepartureDate() {
        return departureDate;
    }

    public void setDepartureDate(LocalDate departureDate) {
        this.departureDate = departureDate;
    }

    public LocalDate getDeadline() {
        return deadline;
    }

    public void setDeadline(LocalDate deadline) {
        this.deadline = deadline;
    }
    
    public int getMaxParticipants() {
        return maxParticipants;
    }

    public void setMaxParticipants(int maxParticipants) {
        this.maxParticipants = maxParticipants;
    }

    public int getCurrentParticipants() {
        return currentParticipants;
    }

    public void setCurrentParticipants(int currentParticipants) {
        this.currentParticipants = currentParticipants;
    }

    public BigDecimal getPricePerAdult() {
        return pricePerAdult;
    }

    public void setPricePerAdult(BigDecimal pricePerAdult) {
        this.pricePerAdult = pricePerAdult;
    }

    public BigDecimal getPricePerChild() {
        return pricePerChild;
    }

    public void setPricePerChild(BigDecimal pricePerChild) {
        this.pricePerChild = pricePerChild;
    }
}