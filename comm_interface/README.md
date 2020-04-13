# QuickFlux-CommInterface
简述
=======
通信模块接口封装。支持TCP、UDP、串口、CAN口等，根据配置文件透明的调用open,close,read,write等接口。

配置文件
=======
在调用本模块时，需要配置通信参数。通信参数的组成如下:<br>
    `[标记名]:[协议名]:[设备名]:[参数序列]`<br>
其中，`标记名`为自定义名称，当出现两个相同名称的设备名时，可作为区分，但保留字default不得使用。<br>
`协议名`取值如下表，标识接口方式: <br>
    * UDP	    *UDP广播*<br>
    * TCP	    *TCP连接*<br>
    * COM	    *串口,包括RS232/RS485*<br>
    * CAN	    *主要支持SocketCAN*<br>

`设备名`约定如下：<br>
    * 当使用网络TCP/UDP时,设备名可根据实际的网络设备节点为eth0,eth1等;<br>
    * 当使用socket CAN时可根据实际的网络设备节点为can0,can1；不使用socket CAN时为CAN设备节点名;<br>
    * 当使用串口(RS232\RS485)为串口设备结点名,如COM1、/dev/ttyS0.<br>

`参数序列`即是各通信方式的参数。每个参数间用逗号","隔开，如<br>
    * Recv01:UDP:eth0:224.0.0.24,8895<br>
    * Recv02:TCP:eth0:255.1.23.4,9876,localhost,12345<br>
    * Recv03:CAN:can0,12500<br>
    * Recv04:COM:/dev/ttymxc1:9600,NONE,8,1<br>

注意事项:<br>
UDP通信方式下，源地址及目标地址可以是如下关键字:<br>
    * localhost		    *IPv4本地地址，相当于127.0.0.1*<br>
    * broadcast	        *IPv4广播地址，相当于是255.255.255.255*<br>
    * any			    *IPv4任意地址，相当于是0.0.0.0*<br>
		
串口通信方式下校验方式如下取值：<br>
    * NONE		无校验<br>
    * EVEN		偶校验<br>
    * ODD		奇校验<br>
    * SPACE		空校验<br>
    * MARK		1校验<br>

另外，为了方便使用本模块进行调试，即在windows桌面上使用本模块对程序进行测试时，不需连接其它接口设备，<br>
本模块默认使用网络UDP进行通信。默认网络通信的参数通过default的标记名称来配置。例如:<br>
    * default:UDP:eth0:224.0.0.17,9865,any,9785<br>
		
接口类
=======
定义:
-------
```cpp
class CCommInterface
{
public:
    explicit CCommInterface();
    CCommInterface(QString file,QString alias);
    ~CCommInterface();

public:
    void setFileName(QString &fileName){
        m_strFileName = fileName;
        m_bFileOk = true;
    }
    void setConnectAlias(QString &alias){
        m_strFileName = alias;
        m_bAliasOk = true;
    }

public:
    bool init();
    int open();
    void close();
    bool hasReadData();
    qint64 readData(QByteArray &data,qint64 maxSize = 1024,int timeOut = 1000);
    qint64 writeData(QByteArray &data);

private:
    bool m_bFileOk;
    bool m_bAliasOk;
    ConfigParse *m_pConfigParser;
    QString m_strFileName;
    QString m_strAlias;
    IDataComm *m_pDataComm;
};
```

使用:
--------
* 初始化：<br>
```cpp
DataCommAdapter adapter(QString(“comm.cfg”),QString("udp"));
```
	或
```cpp
DataCommAdapter adapter；
adapter. setFileName(QString(“comm.cfg”));
adapter. setConnectAlias(QString(“udp”));
```
* 打开：<br>
```cpp
  adapter.open();
```
* 关闭：<br>
```cpp
  adapter.close();
```
* 是否有数据可读:<br>
```cpp
  adapter.hasReadData();
```
* 读数据：<br>
```cpp
  adapter.readData(…)
```
* 写数据：
```cpp
adapter. writeData (…):
```
comm.cfg内容如下：<br>
udp:UDP:eth0:any,12345,localhost,7546<br>
sscom:COM:/dev/ttyS0:9600,NONE,8,1<br>
default:UDP:eth0:225.14.13.20,9852,localhost,7546<br>

例如<br>
```cpp 
DataCommAdapter adapter(QString(“comm.cfg”),QString("udp"))
```
即是查询comm.cfg文件中别名为udp的那条配置数据。<br>