-- ====================================================================================================================
-- ====================================================================================================================
-- Copyright (c) 2017 Ryan Brock. All rights reserved.
-- Licensed under the MIT License. See LICENSE file in the project root for full license information.
--
-- This file is run when the NodeMCU boots.
-- ====================================================================================================================
-- ====================================================================================================================
local IDLE_AT_STARTUP_MS = 10000;

tmr.alarm(1,IDLE_AT_STARTUP_MS,0,function()
    dofile("weather.lua")--Write your program name in dofile
end)