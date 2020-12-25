package com.example.aldajo92.sumobt.activities;

import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.Toast;

import com.example.aldajo92.sumobt.BluetoothService;
import com.microsoft.appcenter.AppCenter;
import com.microsoft.appcenter.analytics.Analytics;
import com.microsoft.appcenter.crashes.Crashes;

/**
 * Created by aldajo92 on 4/14/17.
 */

public class BaseActivity extends AppCompatActivity implements BluetoothService.ConnectedListener {

    private static String TAG = BaseActivity.class.getName();

    BluetoothService bluetoothService;

    private ProgressDialog dialog;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        bluetoothService = new BluetoothService(this);

        bluetoothService.checkBluetoothState(this);
        bluetoothService.setConnectedListener(this);

        AppCenter.start(getApplication(), "2655dca2-0780-4cb7-9721-99a7f082f47d",
                Analytics.class, Crashes.class);
    }

    @Override
    protected void onResume() {
        super.onResume();
        if(!bluetoothService.getIsBTConnected()){

        }
        showMessage("is connected? " + bluetoothService.getIsBTConnected());
    }

    public BluetoothService getBluetoothService() {
        return bluetoothService;
    }

    public void showWaitingOverlay(){
        dialog = ProgressDialog.show(this, "", "Loading. Please wait...", true);
    }

    public void hideWaitingOverlay(){
        if(null != dialog)  dialog.hide();
    }

    public void showMessage(String message){
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
    }

    public void showlog(String message){
        Log.i(TAG, "showlog: " + message);
    }

    public void sendMessage(String data){
        bluetoothService.getBt().send(data + "\n", false);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        bluetoothService.onActivityResult(requestCode, resultCode, data, this);
    }

    @Override
    public void onDeviceConnected() {
        hideWaitingOverlay();
    }

    @Override
    public void onDeviceDisconnected() {
        showWaitingOverlay();
    }

    @Override
    public void onDeviceConnectionFailed() {

    }

    @Override
    public void onDataReceived(String data) {
        processData(data);
    }

    public void processData(String data){

    }
}
