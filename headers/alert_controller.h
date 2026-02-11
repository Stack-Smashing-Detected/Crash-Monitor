#ifndef WARNING_PROMPTS_H
#define WARNING_PROMPTS_H


/**
 * Delcarations for feature that detects decreases in Frames per second or "MEMORY_PRESSURE_EVENT" and warns the user of a potential risk of a system crash.
 */

class AlertController{
private:
    int fps_loss_threshold = 20;
public:

    /**
     * @brief  Constructs an instance of the AlertController
     *
     * @return void
     */
    AlertController();


    std::string detect_significant_fps_decrease(int fps_loss_threshold);
    std::string detect_memory_pressure_event();
    std::string detect_memory_overuse();
};

#endif // WARNING_PROMPTS_H
