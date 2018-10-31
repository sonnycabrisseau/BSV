package com.example.seb.bsv;

import android.Manifest;
import android.content.DialogInterface;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import com.integreight.onesheeld.sdk.OneSheeldConnectionCallback;
import com.integreight.onesheeld.sdk.OneSheeldDevice;
import com.integreight.onesheeld.sdk.OneSheeldError;
import com.integreight.onesheeld.sdk.OneSheeldErrorCallback;
import com.integreight.onesheeld.sdk.OneSheeldManager;
import com.integreight.onesheeld.sdk.OneSheeldScanningCallback;
import com.integreight.onesheeld.sdk.OneSheeldSdk;

import java.io.UnsupportedEncodingException;
import java.util.List;

public class BluetoothConnection  extends AppCompatActivity
{
    /**
     *
     * This class do the connection to the Arduino bluetooth shield
     * todo : need to connect this to the view and after use the arduino object
     * Actually this class is not used but it need to be merge with the MainActivity and after correct everything
     */
    public static final int PERMISSION_REQUEST_CODE = 1;
    private OneSheeldManager oneSheeldManager;
    private OneSheeldDevice arduino;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initOneSheeldSdk();
        scan();
    }

    private void initOneSheeldSdk() {
        OneSheeldSdk.setDebugging(true);
        OneSheeldSdk.init(this);
        oneSheeldManager = OneSheeldSdk.getManager();
        oneSheeldManager.setConnectionRetryCount(1);
        oneSheeldManager.setAutomaticConnectingRetriesForClassicConnections(true);
        oneSheeldManager.addScanningCallback(scanningCallback);
        oneSheeldManager.addConnectionCallback(connectionCallback);
        oneSheeldManager.addErrorCallback(errorCallback);
    }

    public void scan() {
        if (checkAndAskForLocationPermission())
        {
            oneSheeldManager.setScanningTimeOut(20);
            oneSheeldManager.cancelScanning();
            oneSheeldManager.scan();
        }
    }

    private OneSheeldScanningCallback scanningCallback = new OneSheeldScanningCallback() {
        @Override
        public void onDeviceFind(final OneSheeldDevice device)
        {
            Log.i(this.getClass().getName(), "Device found : " + device.getName());
            //if device.name ou mac == ...
            //1Sheeld #DP    60:64:05:90:93:12
            if(device.getAddress().equals("60:64:05:90:93:12"))
            {
                oneSheeldManager.cancelScanning();

                device.connect();
                arduino = device;
                Log.i(this.getClass().getName(), "Connected to : " + arduino.getName());
                Toast.makeText(BluetoothConnection.this, "Connected to : "  + arduino.getName(), Toast.LENGTH_SHORT).show();

            }
        }

        @Override
        public void onScanFinish(List<OneSheeldDevice> foundDevices)
        {
            //scan done
        }
    };

    private OneSheeldConnectionCallback connectionCallback = new OneSheeldConnectionCallback() {
        @Override
        public void onConnect(final OneSheeldDevice device)
        {
            //todo
        }

        @Override
        public void onDisconnect(final OneSheeldDevice device)
        {
            //todo
        }
    };

    private OneSheeldErrorCallback errorCallback = new OneSheeldErrorCallback() {
        @Override
        public void onError(final OneSheeldDevice device, final OneSheeldError error)
        {
            Toast.makeText(BluetoothConnection.this, "Error: " + error.toString() + (device != null ? " in " + device.getName() : ""), Toast.LENGTH_SHORT).show();
        }
    };

    public void sendFirst(View v)
    {
        try
        {
            byte[] data = "peakShavingSansBatterie\n".getBytes("UTF-8");
            arduino.sendSerialData(data);
        }
        catch (UnsupportedEncodingException e)
        {
            e.printStackTrace();
        }
    }

    public void sendSecond(View v)
    {
        try
        {
            byte[] data = "peakShavingAvecBatterie\n".getBytes("UTF-8");
            arduino.sendSerialData(data);
        }
        catch (UnsupportedEncodingException e)
        {
            e.printStackTrace();
        }
    }

    private boolean checkAndAskForLocationPermission()
    {
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            if (ActivityCompat.shouldShowRequestPermissionRationale(this,
                    Manifest.permission.ACCESS_COARSE_LOCATION)) {

                // Show an explanation to the user *asynchronously* -- don't block
                // this thread waiting for the user's response! After the user
                // sees the explanation, try again to request the permission.
                AlertDialog.Builder locationPremissionExplanationDialog = new AlertDialog.Builder(this);
                locationPremissionExplanationDialog.setMessage("Bluetooth scan needs location permission.").setPositiveButton("Allow", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        ActivityCompat.requestPermissions(BluetoothConnection.this,
                                new String[]{Manifest.permission.ACCESS_COARSE_LOCATION},
                                BluetoothConnection.PERMISSION_REQUEST_CODE);
                    }
                }).setNegativeButton("Deny", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Toast.makeText(BluetoothConnection.this, "We can't start scanning until you grant the Location permission.", Toast.LENGTH_SHORT).show();
                    }
                }).create();
                locationPremissionExplanationDialog.show();

            } else {

                // No explanation needed, we can request the permission.

                ActivityCompat.requestPermissions(this,
                        new String[]{Manifest.permission.ACCESS_COARSE_LOCATION},
                        BluetoothConnection.PERMISSION_REQUEST_CODE);
            }
            return false;
        } else {
            return true;
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults)
    {
        if (requestCode == PERMISSION_REQUEST_CODE) {
            if (permissions.length > 0) {
                if (permissions[0].equals(Manifest.permission.ACCESS_COARSE_LOCATION)) {
                    if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                        Toast.makeText(BluetoothConnection.this, "You can start scanning now.", Toast.LENGTH_SHORT).show();
                    } else {
                        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                            if (shouldShowRequestPermissionRationale(Manifest.permission.ACCESS_COARSE_LOCATION))
                                Toast.makeText(BluetoothConnection.this, "We can't start scanning until you grant the Location permission.", Toast.LENGTH_SHORT).show();
                            else
                                Toast.makeText(BluetoothConnection.this, "We can't start scanning until you grant the Location permission from the settings.", Toast.LENGTH_SHORT).show();


                        }
                    }
                }
            }
        }
    }

}
