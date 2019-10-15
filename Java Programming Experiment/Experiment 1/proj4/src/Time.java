import java.text.DecimalFormat;

public class Time {
    int hour;
    int minute;
    int second;

    public Time() {
        this(System.currentTimeMillis());
    }

    public Time(long mill){
        mill /= 1000;
        int m = (int) (mill % (60 * 60 * 24));
        hour = m / 60 / 60;
        second = m % 60;
        minute = (m % (60 * 60)) / 60;
    }

    public int getHour() {
        return hour;
    }

    public int getMinute() {
        return minute;
    }

    public int getSecond() {
        return second;
    }

    @Override
    public String toString() {
        DecimalFormat d = new DecimalFormat("00");
        return "Time{" +
                 d.format(hour) +
                ":" + d.format(minute) +
                ":" + d.format(second) +
                '}';
    }
}
