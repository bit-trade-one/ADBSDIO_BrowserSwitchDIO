[![BTO-logo](https://bit-trade-one.co.jp/wp/wp-content/uploads/2022/05/logo.png)](https://bit-trade-one.co.jp/)

<a href="https://twitter.com/share?ref_src=twsrc%5Etfw" class="twitter-share-button" data-hashtags="Arduino,ブラウザスイッチDIO,BitTradeOne,ビット・トレード・ワン" data-url="https://bit-trade-one.github.io/ADBSDIO_BrowserSwitchDIO/" data-via="BitTradeOne" data-text="ブラウザスイッチDIOサポート" data-show-count="false">Tweetする</a>
<script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>
       
# 出荷時設定
[IPaddress：192.168.1.10](http://192.168.1.10/)  
IPAddress subnet：255.255.25.0  
IPAddress gateway：192.168.1.1  
IPAddress dnsServer：192.168.1.1  

MACaddress：本体基板にシールで添付  

コチラは変更可能です。  
下記のドキュメント項をご確認ください。

# ドキュメント
<details><summary><strong>ADBSDIO概要</strong> </summary>
ADBSDIOと同ネットワークの端末WEBブラウザからリレー接点のON・OFFと接点がHIGHかLOWかの監視が可能です。<br>
またターミナル経由等でMACAddressと接続に使うIPAddressの変更が可能です。<br>
入出力接点は全点絶縁されています。<br>
入出力接点端子はM3のネジ端子とピンソケットを用意しています。お好きな方をご利用ください。<br>
</details>
       
<details><summary><strong>簡易使用方法</strong> </summary>
1.ADBSDIOにUSBかネジ端子から電力を供給します。ネジ端子は8~26Vの電源の入力が可能です。+-に注意して接続してください。<br><br>
2.LANケーブルを接続しADBSDIOをネットワークに接続してください。<br><br>
3.上記と同ネットワーク端末のブラウザから<a href="http://192.168.1.10/">http://192.168.1.10/</a>  に接続します。ここから監視・制御が可能です。<br>
 <img src="https://user-images.githubusercontent.com/85532743/182108096-a6eccd78-2a58-40df-99d0-feb57033f67e.png" width="480px"><br>
</details>

<details><summary><strong>MACAddress書き換え方法</strong> </summary>
1.ADBSDIOと設定するPCをUSBケーブルで接続してください。<br><br>
2.PC画面左下Windowsマークを右クリックし、デバイスマネージャを選び、ADBSDIOのCOMポート番号を確認してください。<br>
<img src="https://user-images.githubusercontent.com/85532743/182106724-7d3e53e5-287a-4822-9f1d-d631c9554114.png" width="720px"><br><br>
3.PCでTeraTermなどターミナルソフトを開き、COMポートを選択します。<br>
<img src="https://user-images.githubusercontent.com/85532743/182112556-10167ed1-e9e4-4793-97b2-fc00776f7911.png" width="720px"><br><br>
4.TeraTermの場合上のメニューから設定>端末を選び、送信の改行はLFを設定してください。<br>
<img src="https://user-images.githubusercontent.com/85532743/182106019-3d67f0bd-68df-48f9-9fba-882c3145b0bb.png" width="720px"><br>
<img src="https://user-images.githubusercontent.com/85532743/182108507-07e1f48a-d883-4dba-9094-e8cd899fbe43.png" width="720px"><br><br>
5.なにかボタンを押すとセッティングモードに入ります。「1」と「Enter」を入力してください。
<img src="https://user-images.githubusercontent.com/85532743/182110253-817634bd-0643-4e1e-b4bb-b7cb5f157b26.png" width="720px"><br><br>
6.NEW_MAC_Address？と聞いてくるので新しいMACAddressを英数字のみで入力してください。<br>
大文字小文字は関係なく大文字に変換されます。<br>
入力に失敗しエラーが出た場合は5秒待ち、キーを入力し設定モードに入るところからやり直してください。<br>
設定ができたらUSBケーブルを抜き差しするかリセットボタンを押して再起動してください。MACAddressが適応されます。<br>
<img src="https://user-images.githubusercontent.com/85532743/182110549-82d2f9dd-dc0f-417c-9e5a-4c2bad7d38f6.png" width="720px"><br>
</details>

<details><summary><strong>IPAddress書き換え方法</strong> </summary>
1.ADBSDIOと設定するPCをUSBケーブルで接続してください。<br><br>
2.PC画面左下Windowsマークを右クリックし、デバイスマネージャを選び、ADBSDIOのCOMポート番号を確認してください。<br>
<img src="https://user-images.githubusercontent.com/85532743/182106724-7d3e53e5-287a-4822-9f1d-d631c9554114.png" width="720px"><br><br>
3.PCでTeraTermなどターミナルソフトを開き、COMポートを選択します。<br>
<img src="https://user-images.githubusercontent.com/85532743/182112556-10167ed1-e9e4-4793-97b2-fc00776f7911.png" width="720px"><br><br>
4.TeraTermの場合上のメニューから設定>端末を選び、送信の改行はLFを設定してください。<br>
<img src="https://user-images.githubusercontent.com/85532743/182106019-3d67f0bd-68df-48f9-9fba-882c3145b0bb.png" width="720px"><br>
<img src="https://user-images.githubusercontent.com/85532743/182108507-07e1f48a-d883-4dba-9094-e8cd899fbe43.png" width="720px"><br><br>
5.なにかボタンを押すとセッティングモードに入ります。「2」と「Enter」を入力してください。
<img src="https://user-images.githubusercontent.com/85532743/182110253-817634bd-0643-4e1e-b4bb-b7cb5f157b26.png" width="720px"><br><br>
6.NEW_IP_Address？と聞いてくるので新しいIPAddressを数字のみで入力してください。<br>
入力に失敗しエラーが出た場合は5秒待ち、キーを入力し設定モードに入るところからやり直してください。<br>
設定ができたらUSBケーブルを抜き差しするかリセットボタンを押して再起動してください。MACAddressが適応されます。<br>
<img src="https://user-images.githubusercontent.com/85532743/182111936-3ad7e6cf-5a61-4a7d-8383-2c09b67a2ef9.png" width="720px"><br>

</details>

<details><summary><strong>ランド説明</strong> </summary>
ADBSDIOにはユーザがパターンカットやハンダブリッジをして設定ができるパッドが4つあります。<br>
恐れ入りますがハンダブリッジ・パターンカットをした場合保証は外れます。<br>
<img src="https://user-images.githubusercontent.com/85532743/182118702-53898fa7-c564-4b55-8915-5920560c63e0.png" width="1023px"><br>
<a href="https://user-images.githubusercontent.com/85532743/182118702-53898fa7-c564-4b55-8915-5920560c63e0.png">クリックで拡大</a><br><br>
1.DI入力かAI入力か<br>
デフォルトでは絶縁のDI入力が選ばれていますが、パターンカットしてAIをハンダブリッジすることにより<br>
非絶縁AI入力が可能になります。なお、お客様の方でファームウェアを修正・書き直していただく必要があります。<br>
詳しくは回路図・ファームウェアをご確認ください。<br><br>

2.カットでブリーダ抵抗無効<br>
パターンをカットすることにより、ブリーダ抵抗が無効になり、入力側に流れる電流が減ります。
詳しくは回路図をご確認ください。<br><br>
       
3.ブリッジでVIN端子有効<br>
ここをハンダブリッジすると、VIN端子より電源供給が可能になります。
詳しくは回路図をご確認ください。<br><br>
       
4.W5500設定<br>
ここをハンダブリッジすると、W5500の設定を変更することが出来ます。
詳しくは回路図・Wiznet社W5500のHPをご確認ください。<br><br>
</details>

<details><summary><strong>ファームウェア書き込み方法</strong> </summary>
       
ファームウェアはハードウェアの中に書き込まれているソフトウェアです。<br>
不具合修正や機能追加された新しいファームウェアが公開された際、<br>
ファームウェアをアップデートすることで新しい機能が使用できます。<br>
       
ADBSDIOはArduinoLeonardo互換のため、ArduinoIDEよりArduinoLeonardoを選択肢してUSBケーブル経由で<br>
ファームウェアを書き込む事ができます。<br>
なお、ArduinoIDEより書き込んだ場合ビット・トレード・ワンで付与したUSBVID・PIDではなくなります。<br>
通常使用では問題ありませんが、ADBSDIOを別の製品として再販売する場合はArduino社・弊社のUSBVID・PIDで販売することは<br>
推奨されていませんのでご注意ください。<br>
</details><br>
  
# サポートファイル等
- 回路図  
- 展開接続図  
- 改造例展開接続図サンプル
- ファームウェア  
- [Q&A](FAQ.md)

# スペシャルサンクス
参考にさせていただきました。  
心より感謝いたします。誠にありがとうございました。

- [W5500](https://www.wiznet.io/product-item/w5500/)
- [Ethernet Library for Arduino](https://github.com/arduino-libraries/Ethernet)  
- Starting Electronics [Analog Inputs and Switches using AJAX](https://startingelectronics.org/tutorials/arduino/ethernet-shield-web-server-tutorial/AJAX-read-switches-analog/)  
- The Strange Storage [Arduino Ethernet シールド [改訂増分版]](https://www.storange.jp/2014/04/arduino-ethernet.html)
