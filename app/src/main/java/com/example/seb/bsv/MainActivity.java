package com.example.seb.bsv;

import android.Manifest;
import android.app.Activity;
import android.content.DialogInterface;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.StrictMode;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AlertDialog;
import android.util.Log;
import android.view.WindowManager;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Toast;

import com.integreight.onesheeld.sdk.OneSheeldConnectionCallback;
import com.integreight.onesheeld.sdk.OneSheeldDevice;
import com.integreight.onesheeld.sdk.OneSheeldError;
import com.integreight.onesheeld.sdk.OneSheeldErrorCallback;
import com.integreight.onesheeld.sdk.OneSheeldManager;
import com.integreight.onesheeld.sdk.OneSheeldScanningCallback;
import com.integreight.onesheeld.sdk.OneSheeldSdk;

import java.util.List;

public class MainActivity extends Activity
{
    public static final int PERMISSION_REQUEST_CODE = 1;
    private OneSheeldManager oneSheeldManager;
    private OneSheeldDevice arduino;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        StrictMode.VmPolicy.Builder builder = new StrictMode.VmPolicy.Builder();
        StrictMode.setVmPolicy(builder.build());

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

            if(device.getAddress().equals("60:64:05:90:93:12")) //1Sheeld #DP    60:64:05:90:93:12
            {
                oneSheeldManager.cancelScanning();

                device.connect();
                arduino = device;
                Log.i(this.getClass().getName(), "Connected to : " + arduino.getName());
                Toast.makeText(MainActivity.this, "Connected to : "  + arduino.getName(), Toast.LENGTH_SHORT).show();

                /*
                La partie ou la webview est instancié
                 */
                JavaScriptInterface javaScriptInterface = new JavaScriptInterface(arduino);

                String myurl = "file:///android_asset/index.html";
                WebView view = (WebView) MainActivity.this.findViewById(R.id.webView);
                view.getSettings().setJavaScriptEnabled(true);

                //envoie de l'interface pour pour les messages bluetooth
                view.addJavascriptInterface(javaScriptInterface, "JavaScriptInterface");
                view.loadUrl(myurl);

                MainActivity.this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
                view.setWebViewClient(new WebViewClient());
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
            Toast.makeText(MainActivity.this, "Error: " + error.toString() + (device != null ? " in " + device.getName() : ""), Toast.LENGTH_SHORT).show();
        }
    };

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
                        ActivityCompat.requestPermissions(MainActivity.this,
                                new String[]{Manifest.permission.ACCESS_COARSE_LOCATION},
                                MainActivity.PERMISSION_REQUEST_CODE);
                    }
                }).setNegativeButton("Deny", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Toast.makeText(MainActivity.this, "We can't start scanning until you grant the Location permission.", Toast.LENGTH_SHORT).show();
                    }
                }).create();
                locationPremissionExplanationDialog.show();

            } else {

                // No explanation needed, we can request the permission.

                ActivityCompat.requestPermissions(this,
                        new String[]{Manifest.permission.ACCESS_COARSE_LOCATION},
                        MainActivity.PERMISSION_REQUEST_CODE);
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
                        Toast.makeText(MainActivity.this, "You can start scanning now.", Toast.LENGTH_SHORT).show();
                    } else {
                        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                            if (shouldShowRequestPermissionRationale(Manifest.permission.ACCESS_COARSE_LOCATION))
                                Toast.makeText(MainActivity.this, "We can't start scanning until you grant the Location permission.", Toast.LENGTH_SHORT).show();
                            else
                                Toast.makeText(MainActivity.this, "We can't start scanning until you grant the Location permission from the settings.", Toast.LENGTH_SHORT).show();


                        }
                    }
                }
            }
        }
    }
}


