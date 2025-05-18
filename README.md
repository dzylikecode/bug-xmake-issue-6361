# xmake构建问题: builddir变量解析错误

## 环境信息

- **硬件平台**: Jetson Orin Nano
- **操作系统**: Ubuntu 22.04
- **xmake版本**: v2.9.9

## 问题描述

在使用xmake构建项目时，发现`$(builddir)`变量没有被正确解析，导致系统尝试在根目录创建文件夹而失败。

### 具体表现

- xmake.lua中的`after_build`脚本尝试使用`$(builddir)/native`路径
- 实际解析结果为`/native`（根目录下的native），而非预期的项目构建目录下
- 由于权限不足，无法在系统根目录创建文件夹，导致构建失败

### 相关代码

在xmake.lua文件中：

```lua
after_build(function (target)
    os.rm("$(builddir)/native")
    os.mkdir("$(builddir)/native")
    os.cp("include/*", "$(builddir)/native")
    os.cp(target:targetfile(), "$(builddir)/native")
end)
```

## 错误日志

```
error: @programdir/core/main.lua:329: @programdir/actions/build/main.lua:148: @programdir/modules/async/runjobs.lua:325: @programdir/core/sandbox/modules/os.lua:223: cannot create directory: /native, Not access because it is busy
stack traceback:
    [C]: in function 'error'
    [@programdir/core/base/os.lua:1075]:
    [@programdir/core/sandbox/modules/os.lua:223]: in function 'mkdir'
    [./xmake.lua:21]: in function 'after_build'
    [@programdir/actions/build/build.lua:127]: in function 'jobfunc'
    [@programdir/modules/async/runjobs.lua:241]:

stack traceback:
        [C]: in function 'error'
        @programdir/core/base/os.lua:1075: in function 'base/os.raiselevel'
        (...tail calls...)
        @programdir/core/main.lua:329: in upvalue 'cotask'
        @programdir/core/base/scheduler.lua:406: in function <@programdir/core/base/scheduler.lua:399>
```

## 期望行为

期望`$(builddir)/native`能正确解析为项目构建目录下的native子目录，而不是系统根目录下的native。