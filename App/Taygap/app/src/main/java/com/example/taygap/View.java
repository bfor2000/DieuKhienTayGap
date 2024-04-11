package com.example.taygap;

import android.util.Log;

import androidx.databinding.BaseObservable;
import androidx.databinding.Bindable;

public class View extends BaseObservable {
    private String kitu = "0000";
    public Boolean b1a= new Boolean(false);

    @Bindable
    public String getKitu() {
        return kitu;
    }

    public void setKitu(String kitu) {
        this.kitu = kitu;
        notifyPropertyChanged(BR.kitu);
    }


    public void b1a(boolean checker) {
        Ham ham = new Ham();
        if(checker)
        Log.e(ham.thay_the_char(2, 'd', kitu), "test");
    }
    public void b1b() {
        Ham ham = new Ham();
        Log.e(ham.thay_the_char(2, 'd', kitu), "test");
    }

    /*
    public void b2a() {
        Ham ham = new Ham();
        Log.e(ham.thay_the_char(2, 'd', kitu), "test");
    }
    public void b2b() {
        Ham ham = new Ham();
        Log.e(ham.thay_the_char(2, 'd', kitu), "test");
    }
    public void b3a() {
        Ham ham = new Ham();
        Log.e(ham.thay_the_char(2, 'd', kitu), "test");
    }
    public void b3b() {
        Ham ham = new Ham();
        Log.e(ham.thay_the_char(2, 'd', kitu), "test");
    }
    public void b4a() {
        Ham ham = new Ham();
        Log.e(ham.thay_the_char(2, 'd', kitu), "test");
    }
    public void b4b() {
        Ham ham = new Ham();
        Log.e(ham.thay_the_char(2, 'd', kitu), "test");
    }
     */
}
