维持三组6个Hash表来存储全部资源数据。
所有资源都以"key-value"的方式存放在Hash表中，key即是别名，value在管理颜色及文本时分别是文本内容和颜色值，管理图片时则是图片名称，支持URL路径。
取图片、文本及颜色资源时，分别以以下方式:<br>
    image@[alias]<br>
    text@[alias]<br>
    color@[alias]<br>
    image-array@[alias]<br>
    text-array@[alias]<br>
    color-array@[alias]<br>
	
[alias]即是资源的别名。

资源管理器分别读取下列3个xml文件的内容，并存储在上述Hash中。
三个xml文件分别如下：<br>
string.xml 存储文本内容<br>
image.xml存储图片<br>
color.xml存储颜色<br>

string.xml文本内容如下:<br>
单独文本:<br>
```
<file version="0.1">
<text alias="greeting">Hello,world</text>
</file>
```
文本组:<br>
```
<file version="0.1">
<text-array alias="greeting">
<text>111111</text>
<text>222222</text>
<text>333333</text>
<text>444444</text>
</text-array>
</file>
```

image.xml文本内容如下:<br>
单独图片:<br>
```
<file version="0.1">
<image alias="greeting">hello.png</image >
</file>
```
图片组:<br>
```
<file version="0.1">
<image-array alias="greeting">
<image>111111.png</image>
<image>222222.png</image>
<image>333333.png</image>
<image>444444.png</image>
</image-array>
</file>
```

color.xml文本内容如下:<br>
单独颜色:<br>
```
<file version="0.1">
<color alias="greeting">#c9c9c9</color>
</file>
```
颜色组:<br>
```
<file version="0.1">
<color-array alias="greeting">
<color>#111111</color>
<color>#222222</color>
<color>#333333</color>
<color>#444444</color>
</color-array>
</file>
```
