
**决定不翻转棋盘，便于坐标统一**

## 棋子的设定

### 位置的表示

按照数学常规定义的二维坐标轴，最下角格子为原点，将a、b、c等字母转成对应1、2、3等数字进行表示。

### 棋子类型

棋子有三个属性：type、color和pos。

```
type    id
king    1
queen   2
bishop  3
knight  4
rook    5
pawn    6
```

另外color为颜色，黑色为1，白色为0 。

### 网络

每次传输时按照读取残局的格式进行传输，这样会很方便。

## 通信

定义Communication类用于通信，其成员变量为 QTcpSocket\* tcpSocket，每次实例化Communication时传入一个QTcpSocket \*。

### 包的定义

定义包格式如下：

```
CHESSPACK YYR
<PACK LENGTH>
<PACK CONTENT>
```

### 封包和拆包的实现

实现pack和unpack函数用于封包和拆包，封包直接字符串拼接即可，拆包时如果无正常包头或者为非完整的包则返回空串，另外传入了一个引用int pos，用于返回包结尾位置的下一位置索引。

### 消息接收机制

在Communication类中实现了类似QTcpSocket的消息接收机制，只不过这里是以一个完整的包内容作为单位的。

实现的函数有：bool hasNextPack();  QString nextPack() ; void close(); 还定义了信号readyReadPack();
