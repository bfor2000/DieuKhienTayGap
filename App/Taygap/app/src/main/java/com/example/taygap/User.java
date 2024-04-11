package com.example.taygap;

public class User {
    private String Dc1;
    private String Dc2;
    private String Dc3;
    private String Dc4;

    public User() {
    }

    public User(String dc1, String dc2, String dc3, String dc4) {
        Dc1 = dc1;
        Dc2 = dc2;
        Dc3 = dc3;
        Dc4 = dc4;
    }

    public String getDc1() {
        return Dc1;
    }

    public void setDc1(String dc1) {
        Dc1 = dc1;
    }

    public String getDc2() {
        return Dc2;
    }

    public void setDc2(String dc2) {
        Dc2 = dc2;
    }

    public String getDc3() {
        return Dc3;
    }

    public void setDc3(String dc3) {
        Dc3 = dc3;
    }

    public String getDc4() {
        return Dc4;
    }

    public void setDc4(String dc4) {
        Dc4 = dc4;
    }

    @Override
    public String toString() {
        return "User{" +
                "Dc1='" + Dc1 + '\'' +
                ", Dc2='" + Dc2 + '\'' +
                ", Dc3='" + Dc3 + '\'' +
                ", Dc4='" + Dc4 + '\'' +
                '}';
    }
}
