//bto_ODA_220830Ver.1.3
//発売時のVendorID:0x22EA
//発売時のProductID:0x0078

#include <SPI.h>
#include <Ethernet2.h>//Ver.1.0.4
#include <EEPROM.h>

byte mac[] = {EEPROM[0x00], EEPROM[0x01], EEPROM[0x02], EEPROM[0x03], EEPROM[0x04], EEPROM[0x05]};
byte ip[] = {EEPROM[0x06], EEPROM[0x07], EEPROM[0x08], EEPROM[0x09]};

IPAddress subnet{EEPROM[0x0A], EEPROM[0x0B], EEPROM[0x0C], EEPROM[0x0D]};
IPAddress gateway{EEPROM[0x0E], EEPROM[0x0F], EEPROM[0x10], EEPROM[0x11]};
IPAddress dnsServer{EEPROM[0x12], EEPROM[0x13], EEPROM[0x14], EEPROM[0x15]};

EthernetServer server(80); // ポート80(HTTP)で通信をするサーバを初期化

String HTTP_req;           //HTTPリクエストを保存
boolean DO0_status = 0;
boolean DO1_status = 0;
boolean DO2_status = 0;
boolean DO3_status = 0;

const int DI0 = A2;
const int DI1 = A3;

const int DO0 = 7;
const int DO1 = 8;

const int STATUS = 4;

void setup()
{
  Serial.setTimeout(20000);




  pinMode(DI0, INPUT);
  pinMode(DI1, INPUT);

  pinMode(DO0, OUTPUT);
  pinMode(DO1, OUTPUT);
  pinMode(STATUS, OUTPUT);
  digitalWrite(STATUS, HIGH);
  if (EEPROM[0x00] == 255 && EEPROM[0x01] == 255 && EEPROM[0x02] == 255 && EEPROM[0x03] == 255 && EEPROM[0x04] == 255 && EEPROM[0x05] == 255) { //EEPROMが初期値なら
    byte LEDtime = 0;
    while (true) { //無限ループ↓
      LEDtime++;
      delay(1);
      Serial_setting();
      if (LEDtime >  254 ) {
        Serial.println(F("MAC_address_Error"));
        digitalWrite(STATUS, !digitalRead(STATUS)); //パイロットランプ点滅
        LEDtime = 0;
      }//無限ループ↑
    }
  }

  Ethernet.begin(mac, ip, dnsServer, gateway, subnet);
  server.begin();
  Serial.begin(9600);
}

void loop()
{

  EthernetClient client = server.available();  //クライアントを取得

  if (client) {  //クライアントを取得したか？
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read(); //クライアントから1バイト（文字）を読み取ります
        HTTP_req += c;  //HTTPリクエストを一度に1文字保存します
        //クライアントリクエストの最後の行は空白で、\nで終わります
        if (c == '\n' && currentLineIsBlank) {//最後の行を受信した後にのみクライアントに応答します

          //標準のhttp応答ヘッダーを送信
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: keep-alive");
          client.println();
          //スイッチ状態のAJAXリクエスト
          if (HTTP_req.indexOf("ajax_switch") > -1) {
            //スイッチの状態を読み取る
            GetAjaxData(client);
          }
          else {  //WebページのHTTPリクエスト
            //Webページを送信-AJAX呼び出しを含むJavaScriptが含まれてる
            client.println(F("<!DOCTYPE html>"));
            client.println(F("<html>"));
            client.println(F("<head>"));
            client.println(F("<meta name=viewport content=width=device-width>"));
            client.println(F("<title>Browser Switch DIO</title>"));
            client.println(F("<script>"));
            client.println(F("function GetSwitchData() {"));

            //client.println(F(""));
            client.println(F("var url = new URL(window.location.href);"));//GET部をブラウザURLから削除
            client.println(F("var params = url.searchParams;"));
            client.println(F("params.delete('mode');"));
            client.println(F("history.replaceState('', '', url.pathname);"));

            client.println(F("nocache = \"&nocache=\" + Math.random() * 1000000;"));
            client.println(F("var request = new XMLHttpRequest();"));
            client.println(F("request.onreadystatechange = function() {"));
            client.println(F("if (this.readyState == 4) {"));
            client.println(F("if (this.status == 200) {"));
            client.println(F("if (this.responseText != null) {"));
            client.println(F("document.getElementById(\"sw_data\")\.innerHTML = this.responseText;"));
            client.println(F("}}}}"));
            client.println(F("request.open(\"GET\", \"ajax_switch\" + nocache, true);"));
            client.println(F("request.send(null);"));
            client.println(F("setTimeout('GetSwitchData()', 3000);"));
            client.println(F("}"));
            client.println(F("</script>"));
            client.println(F("</head>"));
            client.println(F("<div style='padding: 30px 40px 50px 40px; '>"));
            client.println(F("<body style='color:rgb(0,0,0);text-align:left;'>"));
            client.println(F("<body onload=\"GetSwitchData()\">"));
            client.println(F("<p><font size='6' color='#4169E1'><b>Browser Switch DIO</b></font></p>"));

            client.println(F("<p><font size='2' color='#808080'>refresh/3s<br /></font><p>"));
            client.println(F("<div id=\"sw_data\">"));
            client.println(F("</div>"));
            client.println(F("<footer>"));
            client.println(F("<hr>"));
            client.println(F("<p style=text-align:center;><font size='2' color='#808080'>bit-trade-one.LTD<br /></font></p>"));
            client.println(F("</footer>"));
            client.println(F("</body>"));
            client.println(F("</html>"));

          }

          if (HTTP_req.indexOf("DO0=ON") > -1 ) {
            DO0_status = 1;

          } else if (HTTP_req.indexOf("DO0=OFF") > -1 ) {
            DO0_status = 0;

          }  else if (HTTP_req.indexOf("DO1=ON") > -1 ) {
            DO1_status = 1;

          } else if (HTTP_req.indexOf("DO1=OFF") > -1 ) {
            DO1_status = 0;
          }

          //受信したHTTPリクエストをシリアルポートに表示
          Serial.print(HTTP_req);
          HTTP_req = "";            //リクエストで終了、空の文字列
          break;
        }
        //クライアントから受信したテキストのすべての行は\r\nで終わる
        if (c == '\n') {
          //受信したテキストの行の最後の文字
          //改行を開始
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          //クライアントからテキスト文字を受信
          currentLineIsBlank = false;
        }
      } // end if (client.available())
    } // end while (client.connected())
    delay(1);      //Webブラウザにデータを受信する時間を与える
    client.stop(); //接続閉じ
  } // end if (client)
  Serial_setting();//何か入力があればSettingモードへ
}

void GetAjaxData(EthernetClient cl)
{
  ///*---------------------------------------------
  cl.println(F("<form method=GET>"));

  if (digitalRead(DI0)) {
    cl.println(F("<p><b>1:DI0</b> : LOW</p>"));
  }
  else {
    cl.println(F("<p><b>1:DI0</b> : <font color=red><b>HIGH</b></font></p>"));
  }

  if (digitalRead(DI1)) {
    cl.println(F("<p><b>2:DI1</b> : LOW</p>"));
  }
  else {
    cl.println(F("<p><b>2:DI1</b> : <font color=red><b>HIGH</b></font></p>"));
  }
  //*/
  /*---------------------------------------------
    int analog_val_A0 = 0;
    int analog_val_A1 = 0;

    analog_val_A0 = analogRead(DI0);
    analog_val_A1 = analogRead(DI1);

    cl.print(F("<p><b>1:AI0</b> : "));
    cl.print(analog_val_A0);
    cl.println(F("</p>"));

    cl.print(F("<p><b>2:DI1</b> : "));
    cl.print(analog_val_A1);
    cl.println(F("</p>"));

  */

  cl.println(F("<hr>"));
  if (DO0_status == 1) {  // see if checkbox was clicked
    digitalWrite(DO0, HIGH);
    cl.print(F("<p><b>3:DO0</b> : <label for=DO0_ON><input type=radio id=DO0_ON name=DO0 value=ON  checked=checked onclick= submit()>ON</label>"));
    cl.print(F("<label for=DO0_OFF><input type=radio id=DO0_OFF name=DO0 value=OFF onclick= submit()>OFF</label></p>"));
  } else if (DO0_status == 0) {
    digitalWrite(DO0, LOW);
    cl.print(F("<p><b>3:DO0</b> : <label for=DO0_ON><input type=radio id=DO0_ON name=DO0 value=ON   onclick= submit()>ON</label>"));
    cl.print(F("<label for=DO0_OFF><input type=radio id=DO0_OFF name=DO0 value=OFF checked=checked onclick= submit()>OFF</label></p>"));
  }
  cl.println(F("</form>"));
  cl.println(F("<form method=GET>"));
  if (DO1_status == 1) {  // see if checkbox was clicked
    digitalWrite(DO1, HIGH);
    cl.print(F("<p><b>4:DO1</b> : <label for=DO1_ON><input type=radio id=DO1_ON name=DO1 value=ON  checked=checked onclick= submit()>ON</label>"));
    cl.print(F("<label for=DO1_OFF><input type=radio id=DO1_OFF name=DO1 value=OFF onclick= submit()>OFF</label></p>"));
  } else if (DO1_status == 0) {
    digitalWrite(DO1, LOW);
    cl.print(F("<p><b>4:DO1</b> : <label for=DO1_ON><input type=radio id=DO1_ON name=DO1 value=ON   onclick= submit()>ON</label>"));
    cl.print(F("<label for=DO1_OFF><input type=radio id=DO1_OFF name=DO1 value=OFF checked=checked onclick= submit()>OFF</label></p>"));
  }
  cl.println(F("</form>"));
  cl.println(F("<form method=GET>"));

  cl.println(F("</form>"));
}

void Serial_setting() {
  if (Serial.read() != -1) {//何か入力があれば設定モードへ※本モード中WEBサーバは止まります。設定後は要再起動
    String scan_string;
    scan_string = Serial.read();
    scan_string = "";
    Serial.println();
    Serial.println(F("ADBSDIO Setting Mode!"));
    Serial.println(F("TIME OUT 20s_EOL:LF"));
    Serial.println(F("Ver.1.3"));
    Serial.println(F("Current address"));
    Serial.print(F("MAC_"));
    for (int i = 0; i < 6; i++) {
      if (EEPROM[i] <= 16 )Serial.print("0"); //表示用 16以下であれば0埋め
      Serial.print(EEPROM.read(i), HEX);
      if (i < 5)Serial.print(":");//区切り文字表示
    }
    Serial.println();
    Serial.print(F("IP_"));
    for (int i = 6; i < 10; i++) {
      Serial.print(EEPROM.read(i), DEC);
      if (i < 9)Serial.print(".");//区切り文字表示
    }
    Serial.println();
    Serial.print(F("subnet_"));
    for (int i = 10; i < 14; i++) {
      Serial.print(EEPROM.read(i), DEC);
      if (i < 13)Serial.print(".");//区切り文字表示
    }
    Serial.println();
    Serial.print(F("gateway_"));
    for (int i = 14; i < 18; i++) {
      Serial.print(EEPROM.read(i), DEC);
      if (i < 17)Serial.print(".");//区切り文字表示
    }
    Serial.println();
    Serial.print(F("dnsServer_"));
    for (int i = 18; i < 22; i++) {
      Serial.print(EEPROM.read(i), DEC);
      if (i < 21)Serial.print(".");//区切り文字表示
    }
    Serial.println();
    Serial.println(F("Num?"));
    Serial.println(F("1:MAC"));
    Serial.println(F("2:IP"));
    Serial.println(F("3:subnet"));
    Serial.println(F("4:gateway"));
    Serial.println(F("5:dnsServer"));
    Serial.println(F("X:Exit"));

    while (!Serial.available()); //入力があるまで待機
    scan_string = Serial.readStringUntil('\n');
    scan_string.trim();
    Serial.print(F(">>"));
    Serial.println(scan_string);

    //***選択肢1***MACアドレス書き換えモードへ(6バイトの配列)*/
    if (scan_string.equals("1")) {
      Serial.println(F("NEW_MAC_address?(Number Only_sample:8C1F646EC000)"));
      Serial.println(F(">>"));
      while (!Serial.available()); //入力があるまで待機
      scan_string = Serial.readStringUntil('\n');//入力内容の表示
      scan_string.trim();
      Serial.print(F(">>"));
      Serial.println(scan_string);

      if (scan_string.length() == 12) { //文字数がOKか
        Serial.println(F("update!"));

        //12文字のHEXを表している文字列を2文字ずつ結合しEEPROMへ格納
        String i_string;
        char char_buf[5];
        i_string = "0x";
        i_string += scan_string[0];
        i_string += scan_string[1];
        i_string.toCharArray(char_buf, 5);
        EEPROM[0x00] = strtol(char_buf, NULL, 16);

        i_string = "0x";
        i_string += scan_string[2];
        i_string += scan_string[3];
        i_string.toCharArray(char_buf, 5);
        EEPROM[0x01] = strtol(char_buf, NULL, 16);

        i_string = "0x";
        i_string += scan_string[4];
        i_string += scan_string[5];
        i_string.toCharArray(char_buf, 5);
        EEPROM[0x02] = strtol(char_buf, NULL, 16);

        i_string = "0x";
        i_string += scan_string[6];
        i_string += scan_string[7];
        i_string.toCharArray(char_buf, 5);
        EEPROM[0x03] = strtol(char_buf, NULL, 16);

        i_string = "0x";
        i_string += scan_string[8];
        i_string += scan_string[9];
        i_string.toCharArray(char_buf, 5);
        EEPROM[0x04] = strtol(char_buf, NULL, 16);

        i_string = "0x";
        i_string += scan_string[10];
        i_string += scan_string[11];
        i_string.toCharArray(char_buf, 5);
        EEPROM[0x05] = strtol(char_buf, NULL, 16);

        //EEPROMからMAC_addressを読む
        for (int i = 0; i < 6; i++) {
          if (EEPROM[i] <= 16 )Serial.print("0"); //16以下(1桁)であれば0埋め
          Serial.print(EEPROM.read(i), HEX);
          if (i < 5)Serial.print(":");//区切り文字表示
        }
        Serial.println();

      } else {                         //文字数が合わなければエラー
        Serial.println(F("length_Error!"));
      }

      //***選択肢2***ipアドレス書き換えモードへ(4バイトの配列)*/
    } else if (scan_string.equals("2")) {
      Serial.println(F("NEW_IP_address?(Number Only_sample:192168001010)"));
      Serial.println(F(">>"));
      while (!Serial.available()); //入力があるまで待機
      scan_string = Serial.readStringUntil('\n');//入力内容の表示
      scan_string.trim();
      Serial.print(F(">>"));
      Serial.println(scan_string);

      if (scan_string.length() == 12) { //文字数がOKか
        Serial.println(F("update!"));
        //12文字のIPを表している文字列を3文字ずつ結合しEEPROMへ格納
        String i_string;
        char char_buf[5];

        i_string = "";
        i_string += scan_string[0];
        i_string += scan_string[1];
        i_string += scan_string[2];
        EEPROM[0x06] = (byte)i_string.toInt();

        i_string = "";
        i_string += scan_string[3];
        i_string += scan_string[4];
        i_string += scan_string[5];
        EEPROM[0x07] = (byte)i_string.toInt();

        i_string = "";
        i_string += scan_string[6];
        i_string += scan_string[7];
        i_string += scan_string[8];
        EEPROM[0x08] = (byte)i_string.toInt();

        i_string = "";
        i_string += scan_string[9];
        i_string += scan_string[10];
        i_string += scan_string[11];
        EEPROM[0x09] = (byte) i_string.toInt();


        //EEPROMからip_addressを読む
        for (int i = 6; i < 10; i++) {
          Serial.print(EEPROM.read(i), DEC);
          if (i < 9)Serial.print(".");//区切り文字表示
        }
        Serial.println();
      } else {                         //文字数が合わなければエラー
        Serial.println(F("length_Error!"));
      }

      //***選択肢3***subnetアドレス書き換えモードへ(4バイトの配列)*/
    } else if (scan_string.equals("3")) {
      Serial.println(F("NEW_subnet?(Number Only_sample:192168001010)"));
      Serial.println(F(">>"));
      while (!Serial.available()); //入力があるまで待機
      scan_string = Serial.readStringUntil('\n');//入力内容の表示
      scan_string.trim();
      Serial.print(F(">>"));
      Serial.println(scan_string);

      if (scan_string.length() == 12) { //文字数がOKか
        Serial.println(F("update!"));
        //12文字のIPを表している文字列を3文字ずつ結合しEEPROMへ格納
        String i_string;
        char char_buf[5];

        i_string = "";
        i_string += scan_string[0];
        i_string += scan_string[1];
        i_string += scan_string[2];
        EEPROM[0x0A] = (byte)i_string.toInt();

        i_string = "";
        i_string += scan_string[3];
        i_string += scan_string[4];
        i_string += scan_string[5];
        EEPROM[0x0B] = (byte)i_string.toInt();

        i_string = "";
        i_string += scan_string[6];
        i_string += scan_string[7];
        i_string += scan_string[8];
        EEPROM[0x0C] = (byte)i_string.toInt();

        i_string = "";
        i_string += scan_string[9];
        i_string += scan_string[10];
        i_string += scan_string[11];
        EEPROM[0x0D] = (byte) i_string.toInt();


        //EEPROMから読む
        for (int i = 10; i < 14; i++) {
          Serial.print(EEPROM.read(i), DEC);
          if (i < 13)Serial.print(".");//区切り文字表示
        }
        Serial.println();
      } else {                         //文字数が合わなければエラー
        Serial.println(F("length_Error!"));
      }

      //***選択肢4***gatewayアドレス書き換えモードへ(4バイトの配列)*/
    } else if (scan_string.equals("4")) {
      Serial.println(F("NEW_gateway?(Number Only_sample:192168001010)"));
      Serial.println(F(">>"));
      while (!Serial.available()); //入力があるまで待機
      scan_string = Serial.readStringUntil('\n');//入力内容の表示
      scan_string.trim();
      Serial.print(F(">>"));
      Serial.println(scan_string);

      if (scan_string.length() == 12) { //文字数がOKか
        Serial.println(F("update!"));
        //12文字のIPを表している文字列を3文字ずつ結合しEEPROMへ格納
        String i_string;
        char char_buf[5];

        i_string = "";
        i_string += scan_string[0];
        i_string += scan_string[1];
        i_string += scan_string[2];
        EEPROM[0x0E] = (byte)i_string.toInt();

        i_string = "";
        i_string += scan_string[3];
        i_string += scan_string[4];
        i_string += scan_string[5];
        EEPROM[0x0F] = (byte)i_string.toInt();

        i_string = "";
        i_string += scan_string[6];
        i_string += scan_string[7];
        i_string += scan_string[8];
        EEPROM[0x10] = (byte)i_string.toInt();

        i_string = "";
        i_string += scan_string[9];
        i_string += scan_string[10];
        i_string += scan_string[11];
        EEPROM[0x11] = (byte) i_string.toInt();


        //EEPROMから読む
        for (int i = 14; i < 18; i++) {
          Serial.print(EEPROM.read(i), DEC);
          if (i < 17)Serial.print(".");//区切り文字表示
        }
        Serial.println();
      } else {                         //文字数が合わなければエラー
        Serial.println(F("length_Error!"));
      }

      //***選択肢5***dnsServerアドレス書き換えモードへ(4バイトの配列)*/
    } else if (scan_string.equals("5")) {
      Serial.println(F("NEW_dnsServer?(Number Only_sample:192168001010)"));
      Serial.println(F(">>"));
      while (!Serial.available()); //入力があるまで待機
      scan_string = Serial.readStringUntil('\n');//入力内容の表示
      scan_string.trim();
      Serial.print(F(">>"));
      Serial.println(scan_string);

      if (scan_string.length() == 12) { //文字数がOKか
        Serial.println(F("update!"));
        //12文字のIPを表している文字列を3文字ずつ結合しEEPROMへ格納
        String i_string;
        char char_buf[5];

        i_string = "";
        i_string += scan_string[0];
        i_string += scan_string[1];
        i_string += scan_string[2];
        EEPROM[0x12] = (byte)i_string.toInt();

        i_string = "";
        i_string += scan_string[3];
        i_string += scan_string[4];
        i_string += scan_string[5];
        EEPROM[0x13] = (byte)i_string.toInt();

        i_string = "";
        i_string += scan_string[6];
        i_string += scan_string[7];
        i_string += scan_string[8];
        EEPROM[0x14] = (byte)i_string.toInt();

        i_string = "";
        i_string += scan_string[9];
        i_string += scan_string[10];
        i_string += scan_string[11];
        EEPROM[0x15] = (byte) i_string.toInt();


        //EEPROMから読む
        for (int i = 18; i < 22; i++) {
          Serial.print(EEPROM.read(i), DEC);
          if (i < 21)Serial.print(".");//区切り文字表示
        }
        Serial.println();
      } else {                         //文字数が合わなければエラー
        Serial.println(F("length_Error!"));
      }
    } else {//***選択肢以外***抜ける
      Serial.println(F("Setting Mode Exit"));
    }
    Serial.println(F("Please reboot for the settings to take effect"));
    Serial.println(F("bye.Resume after 5 seconds"));
    Serial.println();
    delay(5000);

  }
}
