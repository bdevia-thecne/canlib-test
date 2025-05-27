package com.example.Controller;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/api")
public class HttpController {
 
    @GetMapping("")
    public String init(){
        return "Backend Running";
    }
}
