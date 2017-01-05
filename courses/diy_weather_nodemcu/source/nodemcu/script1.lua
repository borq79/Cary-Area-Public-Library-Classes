THINGSPEAK_API_KEY="5YR83JMEXNNXW86X"

wifi.setmode(wifi.STATION)
wifi.sta.config("libraryessid","librarypassword")
print(wifi.sta.getip())

randomNumber = math.random(0,100)

conn=net.createConnection(net.TCP, false) 
conn:on("receive", function(conn, pl) print(pl) end)
conn:connect(443, "api.thingspeak.com")
conn:send(string.format("POST /update.json HTTP/1.1\r\nHost: api.thingspeak.com\r\n"
    .."Connection: keep-alive\r\nAccept: */*\r\napi_key=%s&field1=%d\r\n\r\n", THINGSPEAK_API_KEY, randomNumber)
http = require("socket.http")
http.get("http://httpbin.org/ip", nil, function(code, data)
    if (code < 0) then
      print("HTTP request failed")
   else
      print(code, data)
    end
  end)

bme280 = require("bme280")
alt=320 -- altitude of the measurement place

re = bme280.init(1,2)
print(string.format("RET=%d", re))
P, T = bme280.baro()
print(string.format("QFE=%d.%03d", P/1000, P%1000))

-- convert measure air pressure to sea level pressure
QNH = bme280.qfe2qnh(P, alt)
print(string.format("QNH=%d.%03d", QNH/1000, QNH%1000))

H, T = bme280.humi()
TC=T/100
TCD=T%100
TF=(((T*9)/5) / 100) + 32
TFD=(((T*9)/5) % 100)
print(string.format("T=%d.%02d C", TC, TCD))
print(string.format("T=%d.%02d F", TF, TFD))
print(string.format("humidity=%d.%03d%%", H/1000, H%1000))
D = bme280.dewpoint(H, T)
print(string.format("dew_point=%d.%02d", D/100, D%100))

-- altimeter function - calculate altitude based on current sea level pressure (QNH) and measure pressure
P = bme280.baro()
curAlt = bme280.altitude(P, QNH)
print(string.format("altitude=%d.%02d", curAlt/100, curAlt%100))

RSSI=wifi.sta.getrssi()
print("RSSI is", RSSI)
--srv=net.createServer(net.TCP) 
--srv:listen(80,function(conn) 
--    conn:on("receive",function(conn,payload) 
--    print(payload) 
--    conn:send(string.format("<h1> Hello, NodeMcu.</h1>\r\nT=%d.%02d\r\nhumidity=%d.%03d%%\r\nADC=%d", T/100, T%100, H/1000, H%1000, adc.read(0)))
--    end) 
--end)


conn=net.createConnection(net.TCP, false) 

--conn:connect(80,"api.thingspeak.com")

conn:on("receive", function(conn, pl)   print("Got Response") end)

conn:on("connection", function(sck, c)
    local response = {}

    print("Connected")
    
    -- if you're sending back HTML over HTTP you'll want something like this instead
    -- local response = {"HTTP/1.0 200 OK\r\nServer: NodeMCU on ESP8266\r\nContent-Type: text/html\r\n\r\n"}

    response[#response + 1] = string.format("GET /update?api_key=5YR83JMEXNNXW86X&field1=%s HTTP/1.1\r\n", t / 10)
    response[#response + 1] = "Host: api.thingspeak.com\r\n"
    response[#response + 1] = "Content-Type: application/x-www-form-urlencoded\r\n"
    response[#response + 1] = "Connection: keep-alive\r\n"
    response[#response + 1] = "Accept: */*\r\n\r\n"

     -- sends and removes the first element from the 'response' table
    local function send(sk)
      if #response > 0 then
        print("sending ...")
        sk:send(table.remove(response, 1))
      else
        print("Closing")
        sk:close()
        response = nil
      end
    end

    -- triggers the send() function again once the first chunk of data was sent
    sck:on("sent", send)

    send(sck)
end)


    
