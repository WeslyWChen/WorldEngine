//
// Created by 30632 on 2025/10/8.
//

#ifndef WORLDENGINE_SIGNALCENTERINTERFACE_H
#define WORLDENGINE_SIGNALCENTERINTERFACE_H

#include <memory>

#include "SignalCenter.h"
#include "SignalCenterApi.h"

namespace WorldEngine
{
    /**
     * @brief create a signal center, provided for unit test code
     * @return a shared pointer to the signal center
     */
    WE_SIGNALCENTER_API std::shared_ptr<SignalCenter> CreateSignalCenter();

    /**
     * @brief get the signal center of single instance
     * @return a reference to the signal center
     */
    WE_SIGNALCENTER_API std::shared_ptr<SignalCenter> GetSignalCenter();

}  // namespace WorldEngine

#endif  // WORLDENGINE_SIGNALCENTERINTERFACE_H
