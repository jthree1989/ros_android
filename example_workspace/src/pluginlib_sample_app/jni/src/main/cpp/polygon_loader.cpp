/*********************************************************************
*
* Software License Agreement (BSD License)
*
*  Copyright (c) 2013, Willow Garage, Inc.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of Willow Garage, Inc. nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*
* Author: Eitan Marder-Eppstein
* Author: Isaac Saito
*********************************************************************/

#include <boost/shared_ptr.hpp>

#include <pluginlib/class_loader.h>
#include <pluginlib_tutorials/polygon_base.h>

#include <android_native_app_glue.h>
#include <android/log.h>

#define  LOG_TAG    "PLUGIN_TEST"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

void android_main(struct android_app* state) {
  LOGD("Starting app.");
  pluginlib::ClassLoader<polygon_base::RegularPolygon> poly_loader("pluginlib_tutorials", "polygon_base::RegularPolygon");

  try
  {
    boost::shared_ptr<polygon_base::RegularPolygon> triangle = poly_loader.createInstance("pluginlib_tutorials/regular_triangle");
    triangle->initialize(10.0);

    //ROS_INFO("Triangle area: %.2f", triangle->area());
    LOGD("Triangle area: %.2f", triangle->area());
  }
  catch(pluginlib::PluginlibException& ex)
  {
    //ROS_ERROR("The plugin failed to load for some reason. Error: %s", ex.what());
    LOGD("The plugin failed to load for some reason. Error: %s", ex.what());
  }

  try
  {
    boost::shared_ptr<polygon_base::RegularPolygon> square = poly_loader.createInstance("pluginlib_tutorials/regular_square");
    square->initialize(10.0);

    //ROS_INFO("Square area: %.2f", square->area());
    LOGD("Square area: %.2f", square->area());
  }
  catch(pluginlib::PluginlibException& ex)
  {
    //ROS_ERROR("The plugin failed to load for some reason. Error: %s", ex.what());
    LOGD("The plugin failed to load for some reason. Error: %s", ex.what());
  }

  while(1) {
    int events;
    struct android_poll_source* source;

    // Poll android events, locking
    while (ALooper_pollAll(-1, NULL, &events, (void**)&source) >= 0) {
        // Process this event
        if (source != NULL) {
            source->process(state, source);
        }

        // Check if we are exiting.
        if (state->destroyRequested != 0) {
            LOGD("APP DESTROYED BYE BYE");
            return;
        }
    }
  }

  return;
}
