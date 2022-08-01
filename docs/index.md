[![BTO-logo](https://bit-trade-one.co.jp/wp/wp-content/uploads/2022/05/logo.png)](https://bit-trade-one.co.jp/)

<a href="https://twitter.com/share?ref_src=twsrc%5Etfw" class="twitter-share-button" data-hashtags="Arduino,ブラウザスイッチDIO,BitTradeOne,ビット・トレード・ワン" data-url="https://bit-trade-one.github.io/ADBSDIO_BrowserSwitchDIO/" data-via="BitTradeOne" data-text="ブラウザスイッチDIOサポート" data-show-count="false">Tweetする</a>
<script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>
       
# 出荷時設定
[IPaddress：192.168.1.10](http://192.168.1.10/)  
IPAddress subnet：255.255.25.0  
IPAddress gateway：192.168.1.1  
IPAddress dnsServer：192.168.1.1  

MACaddress：本体基板にシールで添付  

# ドキュメント
## 概要  
- ADBSDIOと同ネットワークの端末WEBブラウザから接続でき、  
リレー接点のON・OFFと接点がHIGHかLOWかの監視が可能です。  
- またターミナル経由等でMACAddressと接続に使うIPAddressの変更が可能です。  
- 入出力接点は全点絶縁されています。
- 入出力接点端子はM3のネジ端子とピンソケットを用意しています。お好きな方をご利用ください。

## 簡易使用法
- ADBSDIOにUSBかネジ端子から電力を供給します。ネジ端子は8~26Vの電源の入力が可能です。+-に注意して接続してください。
- LANケーブルを接続しADBSDIOをネットワークに接続してください。
- 上記と同ネットワーク端末のブラウザから[192.168.1.10](http://192.168.1.10/)  に接続します。ここから監視・制御が可能です。

## ランド説明

# サポートファイル等
- 回路図  
- 展開接続図  
- ファームウェア  
- [Q&A](FAQ.md)

# スペシャルサンクス
参考にさせていただきました。  
心より感謝いたします。誠にありがとうございました。

- https://www.wiznet.io/product-item/w5500/
- [Ethernet Library for Arduino](https://github.com/arduino-libraries/Ethernet)  
- Starting Electronics [Analog Inputs and Switches using AJAX](https://startingelectronics.org/tutorials/arduino/ethernet-shield-web-server-tutorial/AJAX-read-switches-analog/)  
- The Strange Storage [Arduino Ethernet シールド [改訂増分版]](https://www.storange.jp/2014/04/arduino-ethernet.html)
