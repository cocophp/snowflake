# SnowFlake分布式id生成器，移植到php扩展
## 编写环境在php 7.3.2 下面。
## 使用时，需要先调用 set_work_id( int ) 设置机器id（建议使用ip最后两位组合）
## 调用生成： echo uuid();  
## 安装方式：

```
git clone https://github.com/cocophp/snowflake.git
cd snowflake
sudo root

phpize
./configure
make
make install
```
## make install 之后，一般会在结尾输出模块安装路径，如： "/usr/lib/php/modules/"
## 将该扩展加载到php.ini中

```
vim /etc/php.ini

extension=/usr/lib/php/modules/snowflake.so
```
