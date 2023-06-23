package vendor.alvenan.timer;

@VintfStability
interface ITimer {
    boolean isReady();
    void trigger();
    void reset();
}