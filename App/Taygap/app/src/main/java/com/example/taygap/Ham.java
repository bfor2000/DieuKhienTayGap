package com.example.taygap;

import android.widget.Button;

public class Ham {
    public String thay_the_char(int index, char kitu_thaythe, String chuoi) {
        char[] charArray = chuoi.toCharArray();
        charArray[index] = kitu_thaythe;
        return new String(charArray);
    }
}
