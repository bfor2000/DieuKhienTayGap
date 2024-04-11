package com.example.taygap;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.CountDownTimer;
import android.util.Log;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.example.taygap.databinding.ActivityMainBinding;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {
    Button DC1a,DC1b,DC2a,DC2b,DC3a,DC3b,DC4a,DC4b;
    TextView goc1,goc2,goc3,goc4;
    char d=176;
    String thdk="0000";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button();
        TextView();


        //ActivityMainBinding binding= DataBindingUtil.setContentView(this,R.layout.activity_main);
        //View view_screen= new View();
        //binding.setLogView(view_screen);

        CountDownTimer main=new CountDownTimer(1000,50) {
            @Override
            public void onTick(long millisUntilFinished) {
                sendLogic();
                readgoc();
            }

            @Override
            public void onFinish() {
                this.start();
            }
        }; main.start();

    }

    private void readgoc() {
        FirebaseDatabase database = FirebaseDatabase.getInstance();
        DatabaseReference myRef1 = database.getReference("gocquay");
        myRef1.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                User user= snapshot.getValue(User.class);
                goc1.setText(user.getDc1()+String.valueOf(d));
                goc2.setText(user.getDc2()+String.valueOf(d));
                goc3.setText(user.getDc3()+String.valueOf(d));
                goc4.setText(user.getDc4()+String.valueOf(d));

            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
    }
    private void sendLogic() {
        if(DC1a.isPressed()&&DC1b.isPressed()) data(0,'0',thdk);
        else if(DC1a.isPressed()) data(0,'1',thdk);
        else if(DC1b.isPressed()) data(0,'2',thdk);
        else data(0,'0',thdk);

        if(DC2a.isPressed()&&DC2b.isPressed()) data(1,'0',thdk);
        else if(DC2a.isPressed()) data(1,'1',thdk);
        else if(DC2b.isPressed()) data(1,'2',thdk);
        else data(1,'0',thdk);

        if(DC3a.isPressed()&&DC3b.isPressed()) data(2,'0',thdk);
        else if(DC3a.isPressed()) data(2,'1',thdk);
        else if(DC3b.isPressed()) data(2,'2',thdk);
        else data(2,'0',thdk);

        if(DC4a.isPressed()&&DC4b.isPressed()) data(3,'0',thdk);
        else if(DC4a.isPressed()) data(3,'1',thdk);
        else if(DC4b.isPressed()) data(3,'2',thdk);
        else data(3,'0',thdk);

        Log.e("abc",thdk);
        FirebaseDatabase database1 = FirebaseDatabase.getInstance();
        DatabaseReference myRef = database1.getReference("thdk");
        myRef.setValue(thdk);
    }
    private void Button(){
        DC1a=(Button) findViewById(R.id.DC1a);
        DC1b=(Button) findViewById(R.id.DC1b);
        DC2a=(Button) findViewById(R.id.DC2a);
        DC2b=(Button) findViewById(R.id.DC2b);
        DC3a=(Button) findViewById(R.id.DC3a);
        DC3b=(Button) findViewById(R.id.DC3b);
        DC4a=(Button) findViewById(R.id.DC4a);
        DC4b=(Button) findViewById(R.id.DC4b);
    }
    private void TextView(){
        goc1=(TextView) findViewById(R.id.gocDc1);
        goc2=(TextView) findViewById(R.id.gocDc2);
        goc3=(TextView) findViewById(R.id.gocDc3);
        goc4=(TextView) findViewById(R.id.gocDc4);
    }
    private void data(int index,char kitu,String chuoi){
        Ham ham=new Ham();
        thdk=ham.thay_the_char(index,kitu,chuoi);
    }

}