//
// Created by 30632 on 2025/10/12.
//

#ifndef WORLDENGINE_INPUTHANDLER_H
#define WORLDENGINE_INPUTHANDLER_H

class InputHandler final {
public:
    InputHandler() = default;
    ~InputHandler() = default;
    InputHandler(const InputHandler&) = delete;
    InputHandler& operator=(const InputHandler&) = delete;
    InputHandler(InputHandler&&) = delete;
    InputHandler& operator=(InputHandler&&) = delete;

public:
    void init();
    void shutdown();
};

#endif  // WORLDENGINE_INPUTHANDLER_H
