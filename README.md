LJEngine
========

由OpenGL3.3+及C++编写。支持着色器，不支持固定管线，支持光照，多通道渲染，Effect File。由四部分组成，分别为LJRenderer，LJOpenGL，LJMath，LJGeneral。

LJRenderer

设备接口声明，引擎加载例程。

LJOpenGL

使用OpenGL API实现的渲染器。实现了LJRenderDevice接口，提供OpenGL渲染管线状态配置与读取的接口，包括视口信息，矩阵生成（视图矩阵，模型矩阵，投影矩阵），纹理状态配置，GLSL着色器，顶点渲染例程等。管理器类，如材质管理器，渲染管理器，和若干内部辅助管理器，如纹理对象管理器，着色器管理器，图片资源管理器等。还包括OpenGL的着色器类和着色器程序类。

LJMath

向量、矩阵数学库，以模板的方式定义向量和矩阵类型及其相关运算的接口与函数。包含2、3、4元向量，3x3、4x4矩阵，四元数，并支持整型、浮点（双精度浮点）无符号整型等类型数据。支持绝大多数操作符直接运算。支持向量求模，矢量积（外积，叉积），数量积（内积，点积），单位化，类型互转。支持矩阵初等操作，转置操作，求逆矩阵（使用高斯消去法），基于任意向量的旋转构造，基于四元数的旋转构造，基于任意向量的缩放构造，与四元数互转。

LJGeneral

包含所有与具体图形API无关的引擎组件。材质，纹理，场景图，Mesh，运动控制，摄像机等。

测试

暂时使用glfw进行窗口管理，配置OpenGL profile和接受事件。使用glfw的定时器实现引擎定时器接口。Frame Listener同样基于glfw实现。封装了基于Assimp的模型加载例程，暂时由测试程序使用。
