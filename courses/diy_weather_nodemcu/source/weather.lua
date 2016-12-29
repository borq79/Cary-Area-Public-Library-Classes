-- ====================================================================================================================
-- ====================================================================================================================
-- Copyright (c) 2017 Ryan Brock. All rights reserved.
-- Licensed under the MIT License. See LICENSE file in the project root for full license information.
--
-- This file is run when the NodeMCU boots.
-- This will connect to the WiFi and start up the mini HTTP server
-- ====================================================================================================================
-- ====================================================================================================================

function trim(s)
  return (s:gsub("^%s*(.-)%s*$", "%1"))
end

-- ====================================================================================================================
-- Load the Configuration
-- ====================================================================================================================
print("\n-----------------------------------")
print(" Starting Weather Station ...")
print("-----------------------------------")

if file.open("weather.config") then
  configLine = file.readline()

  while configLine do
    configName, configValue = configLine:match("([^,]+)\:([^,]+)")
    configName = trim(configName)
    configValue = trim(configValue)

    print(string.format("Setting [%s] to [%s]", configName, configValue))
    _G[configName] = configValue
    configLine = file.readline()
  end

  file.close()
end

-- ====================================================================================================================
-- Connect to the wifi
-- ====================================================================================================================
wifi.setmode(wifi.STATION)
 

station_cfg={}
station_cfg.ssid=ssid
station_cfg.pwd=wifipassword
station_cfg.save=true
station_cfg.auto=true
connectionStatus = wifi.sta.config(station_cfg) 

if connectionStatus == true then
    print(string.format("Successfully Connected to [%s]", ssid))
    print("Connected IP Details: ", wifi.sta.getip())
else
    print(string.format("Failed to connect to [%s]", ssid))
end




-- ====================================================================================================================
-- Start the HTTP server
-- ====================================================================================================================
-- srv=net.createServer(net.TCP)
-- srv:listen(80,function(conn)
--     conn:on("receive",function(conn,payload)
--     print(payload)
--     conn:send(string.format("<h1> Hello, NodeMcu.</h1>\r\nT=%d.%02d C\r\nT=%d.%02d F\r\nhumidity=%d.%03d%%\r\nADC=%d\r\n", TC, TCD, TF, TFD, H/1000, H%1000, adc.read(0)))
--     end)
-- end)
