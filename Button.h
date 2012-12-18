#define NUM_BUTTONS 1
#define DEBOUNCE_MS 5

struct Button {
    int pin;
    volatile unsigned long lastChange;
    int bounceTime;
    void (*onPress)();
    void (*onRelease)();
};

class ButtonManager {
    public:
        static void registerButton(int pin, int bounceTime = 5, void(*onPress)() = 0, void(*onRelease)() = 0);
        static void onInterrupt();
    private:
        static Button mButtons[NUM_BUTTONS];
        static int mNumButtons;

};

