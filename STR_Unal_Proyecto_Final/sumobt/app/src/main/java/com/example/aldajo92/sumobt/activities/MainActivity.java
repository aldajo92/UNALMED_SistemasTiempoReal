package com.example.aldajo92.sumobt.activities;

import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.widget.TextView;

import com.example.aldajo92.sumobt.R;
import com.github.mikephil.charting.charts.LineChart;
import com.github.mikephil.charting.components.XAxis;
import com.github.mikephil.charting.components.YAxis;
import com.github.mikephil.charting.data.Entry;
import com.github.mikephil.charting.data.LineData;
import com.github.mikephil.charting.data.LineDataSet;
import com.github.mikephil.charting.interfaces.datasets.ILineDataSet;
import com.jmedeisis.bugstick.Joystick;
import com.jmedeisis.bugstick.JoystickListener;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends BaseActivity {

    Joystick joystick;
    TextView textView;

    private LineChart lineChart;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initViews();
        initLinearData();
        initDataSet();
    }

    private void initViews() {
        joystick = findViewById(R.id.joystick);
        textView = findViewById(R.id.textview);
        lineChart = findViewById(R.id.lineaChart_entries);
        joystick.setJoystickListener(new JoystickListener() {
            @Override
            public void onDown() {
                showlog("down");
            }

            @Override
            public void onDrag(float degrees, float offset) {
                showlog("drag degree=" + degrees + " offset=" + offset);
                showlog("m;" +
                        (int) (offset * 400 * Math.sin(Math.toRadians(degrees))) +
                        ";" +
                        (int) (offset * 400 * Math.cos(Math.toRadians(degrees)))
                );
                if (getBluetoothService().getIsBTConnected()) {
                    sendMessage("m;" +
                            (int) (offset * 400 * Math.sin(Math.toRadians(degrees))) +
                            ";" +
                            (int) (offset * 400 * Math.cos(Math.toRadians(degrees)))
                    );
                }
            }

            @Override
            public void onUp() {
                sendMessage("m;0;0");
            }
        });
    }

    private List<Entry> linearEntryList;
    private LineDataSet set1;

    private void initDataSet() {
        set1 = new LineDataSet(linearEntryList, "DataSet");

        set1.setDrawIcons(false);
//        set1.setColor(ContextCompat.getColor(this, R.color.clear_color));
//        set1.setCircleColor(Color.WHITE);
        set1.setLineWidth(3f);
//        set1.setCircleRadius(6f);
//        set1.setCircleHoleRadius(4f);
        set1.setDrawCircleHole(false);
//        set1.setCircleHoleColor(Color.BLACK);
        set1.setDrawValues(false);
        set1.setValueTextSize(9f);
        set1.setDrawFilled(false);
        set1.setFormLineWidth(1f);
        set1.setMode(LineDataSet.Mode.CUBIC_BEZIER);
        set1.setFormSize(15f);

        set1.setFillColor(Color.BLACK);

        ArrayList<ILineDataSet> dataSets = new ArrayList<>();
        dataSets.add(set1);

        lineChart.setData(new LineData(dataSets));
    }

    private void initLinearData() {

        lineChart.getDescription().setEnabled(false);
        lineChart.getLegend().setEnabled(false);

        lineChart.setPinchZoom(false);

        lineChart.setScaleXEnabled(false);
        lineChart.setScaleYEnabled(false);

        XAxis xAxis = lineChart.getXAxis();
        xAxis.enableGridDashedLine(10f, 10f, 0f);
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        xAxis.setGranularity(1f);

        YAxis axisLeft = lineChart.getAxisLeft();
        axisLeft.removeAllLimitLines();
        axisLeft.setDrawZeroLine(false);
        axisLeft.setDrawLimitLinesBehindData(false);
        axisLeft.setDrawAxisLine(true);
        axisLeft.setDrawGridLines(true);
        axisLeft.setDrawLabels(true);
        axisLeft.setEnabled(true);
//        axisLeft.setAxisMinimum(-2f);

        YAxis axisRight = lineChart.getAxisRight();
        axisRight.setDrawAxisLine(false);
        axisRight.setDrawGridLines(false);
        axisRight.setEnabled(false);
//        axisRight.setAxisMinimum(-2f);

    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        boolean handled = false;
        if ((event.getSource() & InputDevice.SOURCE_GAMEPAD)
                == InputDevice.SOURCE_GAMEPAD) {
            if (event.getRepeatCount() == 0) {
                showlog("onKeyDown: " + keyCode);
//                switch (keyCode) {
//                    // Handle gamepad and D-pad button presses to
//                    // navigate the ship
//
//                    default:
//                        if (isFireKey(keyCode)) {
//                            // Update the ship object to fire lasers
//                            handled = true;
//                        }
//                        break;
//                }
            }
            if (handled) {
                return true;
            }
        }
        return super.onKeyDown(keyCode, event);
    }

    @Override
    public boolean onGenericMotionEvent(MotionEvent event) {
        // Check that the event came from a game controller
        if ((event.getSource() & InputDevice.SOURCE_JOYSTICK) ==
                InputDevice.SOURCE_JOYSTICK &&
                event.getAction() == MotionEvent.ACTION_MOVE) {

            // Process all historical movement samples in the batch
            final int historySize = event.getHistorySize();

            // Process the movements starting from the
            // earliest historical position in the batch
            for (int i = 0; i < historySize; i++) {
                // Process the event at historical position i
                processJoystickInput(event, i);
            }

            // Process the current movement sample in the batch (position -1)
            processJoystickInput(event, -1);
            return true;
        }

        return super.onGenericMotionEvent(event);
    }

    private void processJoystickInput(MotionEvent event, int historyPos) {

        InputDevice mInputDevice = event.getDevice();

        // Calculate the horizontal distance to move by
        // using the input value from one of these physical controls:
        // the left control stick, hat axis, or the right control stick.
        float x = getCenteredAxis(event, mInputDevice,
                MotionEvent.AXIS_X, historyPos);
        if (x == 0) {
            x = getCenteredAxis(event, mInputDevice,
                    MotionEvent.AXIS_HAT_X, historyPos);
        }
        if (x == 0) {
            x = getCenteredAxis(event, mInputDevice,
                    MotionEvent.AXIS_Z, historyPos);
        }

        // Calculate the vertical distance to move by
        // using the input value from one of these physical controls:
        // the left control stick, hat switch, or the right control stick.
        float y = getCenteredAxis(event, mInputDevice,
                MotionEvent.AXIS_Y, historyPos);
        if (y == 0) {
            y = getCenteredAxis(event, mInputDevice,
                    MotionEvent.AXIS_HAT_Y, historyPos);
        }
        if (y == 0) {
            y = getCenteredAxis(event, mInputDevice,
                    MotionEvent.AXIS_RZ, historyPos);
        }

        // Update the ship object based on the new x and y values
        Log.i("CONTROL", "processJoystickInput x: " + x);
        Log.i("CONTROL", "processJoystickInput y: " + y);

        if (getBluetoothService().getIsBTConnected()) {
            sendMessage("m;" +
                    (int) (-y * 200) +
                    ";" +
                    (int) (x * 200)
            );
        }
    }

    private static float getCenteredAxis(MotionEvent event, InputDevice device, int axis, int historyPos) {
        final InputDevice.MotionRange range =
                device.getMotionRange(axis, event.getSource());

        // A joystick at rest does not always report an absolute position of
        // (0,0). Use the getFlat() method to determine the range of values
        // bounding the joystick axis center.
        if (range != null) {
            final float flat = range.getFlat();
            final float value =
                    historyPos < 0 ? event.getAxisValue(axis) :
                            event.getHistoricalAxisValue(axis, historyPos);

            // Ignore axis values that are within the 'flat' region of the
            // joystick axis center.
            if (Math.abs(value) > flat) {
                return value;
            }
        }
        return 0;
    }

    private List<Float> incomesData;

    private void setEntries(List<Float> incomesData) {
        this.incomesData = incomesData;
        if (incomesData != null && !incomesData.isEmpty()) {
            linearEntryList = new ArrayList<>();
            int entriesSize = incomesData.size();
            for (int index = 0; index < entriesSize; index++) {
                Float entryNoteModel = incomesData.get(index);
                linearEntryList.add(new Entry(index, entryNoteModel));
            }

            ArrayList<ILineDataSet> dataSets = new ArrayList<>();
            dataSets.add(set1);

            lineChart.setData(new LineData(dataSets));

            if (lineChart.getData() != null && lineChart.getData().getDataSetCount() > 0) {
                set1 = (LineDataSet) lineChart.getData().getDataSetByIndex(0);
                set1.setValues(linearEntryList);
                lineChart.getData().notifyDataChanged();
            }
        } else {
            lineChart.clear();
        }

        lineChart.notifyDataSetChanged();
        lineChart.invalidate();
    }

    private void addEntry(float value) {
        int size = 0;
        if (linearEntryList != null) {
            size = linearEntryList.size();
        }
        set1.addEntry(new Entry(size, value));
        lineChart.getData().notifyDataChanged();
        lineChart.notifyDataSetChanged();
        lineChart.invalidate();
    }

    List<Float> values = new ArrayList<>();
    int size = 100;

    @Override
    public void processData(String data) {
        textView.setText(data);
        float value = Float.parseFloat(data);
        if(values.size() > 50){
            values.remove(0);
        }
        values.add(value);
        setEntries(values);
    }
}
