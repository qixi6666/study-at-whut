package travel.controller;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import travel.service.TourService;
import travel.model.TourGroup;
import travel.model.TourOrder;  // 添加这行导入语句
@Controller
@RequestMapping("/tours")
public class TourController {
    private final TourService tourService;

    public TourController(TourService tourService) {
        this.tourService = tourService;
    }

    @GetMapping
    public String showTourPage(@RequestParam String tourId, Model model) {
        TourGroup tour = tourService.getTourGroupById(tourId);
        model.addAttribute("tour", tour);
        return "tour";
    }

    @GetMapping("/list")
    public String listTours(Model model) {
        model.addAttribute("tours", tourService.getAllTourGroups());
        return "tour-list";
    }

    @PostMapping("/book")
    public String bookTour(@RequestParam String tourId,
                         @RequestParam String name,
                         @RequestParam String phone,
                         @RequestParam int adults,
                         @RequestParam int children,
                         Model model) {
        try {
            String orderId = tourService.createTourOrder(tourId, name, phone, adults, children);
            model.addAttribute("orderId", orderId);
            model.addAttribute("name", name);
            model.addAttribute("phone", phone);
            model.addAttribute("adults", adults);
            model.addAttribute("children", children);
            model.addAttribute("tour", tourService.getTourGroupById(tourId));
            return "booking-success";
        } catch (Exception e) {
            model.addAttribute("error", e.getMessage());
            model.addAttribute("tour", tourService.getTourGroupById(tourId));
            return "tour";
        }
    }

    @GetMapping("/orders/{orderId}")
    public String viewOrder(@PathVariable String orderId, Model model) {
        TourOrder order = tourService.getOrderById(orderId);
        if (order == null) {
            model.addAttribute("error", "订单不存在");
            return "error";
        }
        model.addAttribute("order", order);
        return "order-detail";
    }
}