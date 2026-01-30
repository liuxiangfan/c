# <font face="仿宋" color="red">Robotics招新题</font>
## 刘相凡
### **一.概念解释**
1. **嵌入式系统**
   1. 理解：嵌入式系统是一种专用于执行特定任务的计算机系统，它通常作为一个更大设备的一部分被“嵌入”其中，就像是一件产品的大脑，被预先编程来完成各种任务。
   2. 组成：硬件+软件。
         硬件：处理器、存储器、外围电路-->集成在一块板子上。
         软件：底层驱动、操作系统、应用程序
   3. 设备：智能手机,无人机,机器人，智能汽车,红绿灯,ETC（几乎任何带电路板、按钮或显示屏的设备，它的内部都可能有多个嵌入式系统正在起作用）*可以说嵌入式设备无处不在*    
2. **单片机和STM32**
   1. 单片机:单片机就是把一整个计算机系统集成到一块芯片上的集成电路。常见的单片机类型有8位、16位、32位。
   2. STM32:STM32是ST公司推出的一款基于ARM Cortex-M内核开发出的32位单片机家族。
   3. 关系:STM32是单片机的一种。如果说单片机是一个大类、一个概念，那么STM32就是一个具体的产品。
3. **结构**
   1. 冯·诺依曼体系结构：程序指令和数据储存在同一块内存中，共享同一条总线，不能同时进行指令和数据的访问。
   2. 哈佛结构：程序指令和数据存储在两个独立的内存中，拥有各自的总线,可以同时进行指令和数据的访问。
   3. STM32的内核是哈佛结构，但是有所改进：STM32的内核有独立的程序指令总线与数据储存总线，这是哈佛结构核心思想的体现，但是它的内存采用统一编址，也就是它的数据存储器、程序存储器等被放到了一个地址中。
   *既高效率又简便灵活*
4. **名词解释**
   1. **MCU**：微控制器单元，俗称单片机。它是一块集成了一台微型计算机所有核心部件的芯片。包含了CPU、存储器、输入和输出接口和各种外设。
   2. **外设**：外部设备，是单片机中的一个模块。它们能够扩展单片机的功能。但是它并不仅是外部物理设备，一些常用的外设被集成到单片机内部。
   3. **并行串行**：**并行**是多个数据同时通过多条数据线传输，速度快，抗干扰能力差。
   **串行**是数据依次通过单条数据线传输，速度相对慢，抗干扰能力强。
   4. **同步异步**：**同步通信**：用统一的时钟信号来使数据的收发双方保持同步。常用于短距离、高实时性的通信。
   **异步通信**：数据收发双方使用独立的时钟信号。适用于长距离、低实时性的通信。
   5. **串口**：串行接口。串口是一种应用十分广泛的通讯接口，串口成本低、容易使用、通信线路简单，可实现两个设备的互相通信。单片机的串口可以使单片机与各式各样的设备互相通信，极大地扩展了单片机的应用范围。
   6. **GPIO**：通用输入输出口。它的引脚功能可以灵活配置。有浮空输入，上拉输入，下拉输入，模拟输入，推挽输出，开漏输出，复用推挽输出，复用开漏输出8种工作模式。
   7. **DMA**：绕过CPU，直接访问内存。节省CPU的资源。
   8. **ADC**：模数转换器。将模拟信号转换为数字信号。
   9.  **DAC**：数模转换器。将数字信号转换为模拟信号。
   10. **TIM**：定时器。它是单片机内部的硬件资源，有计时、计数、产生定时中断、输出PWM等作用。
   11. **RTC**：Real Time Clock,实时时钟。用于长时间的计时，通常有独立电源，用于记录年、月、日等信息。
   12. **SDIO**：Secure Digital Input and Output,安全数字输入输出。用于接入SD卡·蓝牙模块等SDIO接口的设备。
   13. **USB**：Universal Serial Bus通用串行总线。实现单片机与计算机或其他设备之间的通信。
   14. **CAN**：Controller Area Network,控制器局域网。是一种异步串行通信总线，抗干扰能力强。
   15. **SPI**：Serial Periphral Interface,串行外设接口。是一种同步串行通信总线，有4根线，速度快，支持总线挂载多设备。
   16. **IIC**：Inter-Intergrated Cricuit，集成电路总线。是一种同步串行总线，只需要两根线：SDA和SCL，支持总线挂载多设备，节省引脚，但速度不如SPI。
   17. **USART**：Universal Synchronous/Asynchronous Receiver/Transmitter，同步/异步串口通信。结构简单常用TX和RX两根线通信。
   [![pVfPY4I.png](https://s21.ax1x.com/2025/09/14/pVfPY4I.png)](https://imgse.com/i/pVfPY4I)
**********
### **二.C语言基础**
1. **结构体(struct)**
   1. 用途：数据打包，不同类型变量的集合。
   2. 结构：typedef struct{int a;char b;float c;}结构体名称;
   3. 调用结构体成员：结构体名称.a= ;
   ```
   #include <stdio.h>
   typedef struct 
   {
      char category[20];//类别
      float price;//价格
      char producer[20];//生产厂商
      char materials[100];//原料
   }Item;
   int main()
   {
      Item item;
      int n;
      printf("Catagory=");
      scanf("%s",&item.category);
      printf("Price=");
      scanf("%f",&item.price);
      printf("Producer=");
      scanf("%s",&item.producer);
      printf("Number of materials=");
      scanf("%d",&n);
      for(int i=0;i<n;i++)
      {
         printf("Material %d=",i+1);
         scanf("%s",&item.materials[i]);
      }
      return 0;
   }
   ```
2. **项目程序设计开发结构and指针**
   1. 预处理器:编译处理的第一个步骤，它在编译器工作之前对源代码进行一些处理。如#include，#define。
   2. 头文件:是项目的声明文件和接口文件（通常以.h作为后缀）。告诉别人我能做什么。
   3. 库函数:是由芯片厂商提供的预先编写好的函数集合，用于操作单片机的内部外设（GPIO等）。
   4. 指针是记录地址的变量。
   ```
   #include<stdio.h>
   void swap(int *pa,int *pb);
   int main()
   {
      int a,b;
      scanf("%d%d",&a,&b);
      swap(&a,&b);
      printf("a=%d,b=%d",a,b);
       return 0;s
   }
   void swap(int *pa,int *pb)
   {
      int x=*pa;
       *pa=*pb;
      *pb=x;
   }
   ```
3. **2/8/16进制与位单位**
    ```
      #include <stdio.h>
      int main()
      {
         int num1,num2,sum;
         long long int result=0;
         long long int x=1;
         printf("Enter two numbers(十位数):");
         scanf("%d%d",&num1,&num2);
         sum=num1+num2;
         while(sum!=0)
         {
            result+=(sum%2)*x;
            sum=sum/2;
            x*=10;
         }
         printf("二进制数：%lld",result);
         return 0;
      }
   ```
**********

[![pVWvkFK.jpg](https://s21.ax1x.com/2025/09/14/pVWvkFK.jpg)](https://imgse.com/i/pVWvkFK)