#  控件
支持一些常用控件，包括图片，显示站点图片，普通文本、站点文本、时间、视频窗口、动画、线路图进度动画等等控件，它们的功能及介绍如下:<br>
控件名称|描述及说明
:--:|--
KImage|显示普通图片。有如下属性:<br>src: url类型，指定图片的源<br>fitType: 拉伸还是平铺<br>
KStationImage|显示站点关联图片，即跟随站点变化的图片。有如下属性:<br>src: url类型，指定图片的源<br>index: 源中的索引号<br>
KLabel|显示普通文本的标签控件。有如下属性:<br>hAlignment: 水平对齐方式<br>vAlignment: 竖直对齐方式<br>rotate: 旋转角度<br>text: 文本内容，可以是文本字面值也可以是url地址<br>font: 字体相关，指定显示的文本字体<br>textColor: 指定字体的颜色<br>
KStationLabel|显示站点关联文本的标签。有如下属性:<br>hAlignment: 水平对齐方式<br>vAlignment: 竖直对齐方式<br>rotate: 旋转角度<br>text: 文本的源，为url<br>index: 文本在源中的站点索引<br>font: 字体相关，指定显示的文本字体<br>textColor: 指定字体的颜色<br>
KMediaPlayer|显示视频播放器窗口的标签。有如下属性:<br>src: 视频源，url地址<br>status: 播放、停止等状态<br>
KPathSlider|显示线路路径的控件。有如下属性:<br>foreColor: 未过站颜色<br>backColor: 已经过站的颜色<br>count: 站点个数<br>
KTimePanel|显示时间的控件。有如下属性:<br>format: 显示格式<br>type: 显示样式，以钟表的样式显示还是纯数字显示<br>
KWeatherPanel|显示天气的控件。有如下属性:<br>src: 表示天气情况的图片的源为url源地址<br>index: 图片源的索引号<br>
KTempMeter|显示温度计的控件。有如下属性:<br>format: 显示格式，用来表示是以摄氏度还是华氏度显示，取值为"F"或者"C",分别表示华氏度和摄氏度<br>type: 显示方式，用来指定是以温度计样式来显示还是纯文字来显示<br>
KMarquee|显示走马灯的控件。有如下属性:<br>orientation: 走马灯方向，可以是从右到左，从下到上<br>text: 显示的文本，可以是字符串字面值也可以是url<br>
KToastBar|显示对话提示框的控件。有如下属性:<br>visible: 控制是否显示<br>foreImage: 前景图片，如果未设置前景图片，则是透明的<br>text: 提示的文本内容,可以是文本字面量，也可以是url地址指定的文本内容<br>duration: 持续时间，-1为永久显示，0为不显示，其它为显示时间，单位是毫秒<br>textColor: 提示文本的显示颜色<br>font: 文本的字体等<br>

另外，以下属性是上述所有控件都具有的共同属性:<br>
x: 横坐标<br>y: 纵坐标<br>width: 宽度<br>height: 高度<br>

