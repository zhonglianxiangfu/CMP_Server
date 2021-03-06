#ifndef _CODE_DEF_H_
#define _CODE_DEF_H_

typedef struct _operate_code
{
   char m_sId[5];           /* 操作码ID */
   int  (*pfnFun)( char *opczBuf, int *opiBufLen );
   int  m_nInType;          /* 输入类型0-定长 1-变长 */
   int  m_nInAB;            /* 输入字段类型 0-ASCII 1-BCD */
   int  m_nInLen;           /* 输入字段长度 */
   int  m_nInLenType;       /* 输入字段长度字段类型 */
   int  m_nInLenLen;        /* 输入字段长度字段长度 */
   int  m_nOutType;         /* 输出类型0-定长 1-变长 */
   int  m_nOutAB;           /* 输出字段类型 0-ASCII 1-BCD */
   int  m_nOutLen;          /* 输出字段长度 */
   int  m_nOutLenType;      /* 输出字段长度字段类型 0-ASCII 1-BCD 2-HEX */
   int  m_nOutLenLen;       /* 输出字段长度字段长度 */
   char m_sRemark[20];      /* 说明 */
} OperateCode;
OperateCode stOperCode[257]=
{
   {"02", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "密码键盘序号"},      /*读密码键盘序号      */
   {"03", NULL         , 0,0, 1  , 0,0, 0,1, 20 , 0,0,  "卡号"        },      /*读卡号              */
   {"04", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "二三磁道密文"},      /*读二三磁道          */
   {"05", NULL         , 0,0, 1  , 0,0, 0,0, 8  , 0,0,  "密码"        },      /*密码键盘输密码      */
   {"06", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "数量"        },      /*输数量数据          */
   {"07", NULL         , 0,0, 1  , 0,0, 0,1, 12 , 0,0,  "金额"        },      /*输金额              */
   {"08", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "金融数据"    },      /*输金融应用数据      */
   {"09", NULL         , 0,0, 1  , 0,0, 1,0, 0  , 2,1,  "商务数据"    },      /*输商务应用数据      */
   {"0A", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "年份"        },      /*输YYYYMMDD          */
   {"0B", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "年份"        },      /*输YYYYMM            */
   {"0C", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "数据"        },      /*输数据              */
   {"0D", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "计算鉴别码"  },      /*计算鉴别码          */
   {"0E", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "计算签名"    },      /*计算签名            */
   {"0F", NULL         , 0,0, 1  , 0,0, 0,0, 27 , 0,0,  "冲正信息"    },      /*取冲正信息          */
   {"10", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "应用版本号"  },      /*取应用版本号        */
   {"11", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "功能版本号"  },      /*取功能版本号        */
   {"12", NULL         , 0,0, 1  , 0,0, 0,0, 23 , 0,0,  "机器号"      },      /*取终端出厂编号      */
   {"13", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "加密"        },      /*加密发送数据        */
   {"14", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "解密"        },      /*解密接收数据        */
   {"15", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "账单支付数据"},      /*提取帐单支付数据    */
   {"16", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "更新终端参数"},      /*更新终端参数        */
   {"17", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "更新KEK参数" },      /*更新KEK参数         */
   {"18", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "更新菜单参数"},      /*更新菜单参数        */
   {"19", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "更新功能提示"},      /*更新功能提示        */
   {"1A", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "更新操作提示"},      /*更新操作提示        */
   {"1B", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "更新首页信息"},      /*更新首页信息        */
   {"1C", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "更新打印模板"},      /*更新打印模板        */
   {"1D", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "锁定密码键盘"},      /*锁定密码键盘        */
   {"1E", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "帐单信息"    },      /*显示并存储帐单信息  */
   {"1F", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "更新错误提示"},      /*更新错误提示        */
   {"20", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "存储短信"    },      /*存储短信            */
   {"21", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "打印数据"    },      /*打印数据            */
   {"22", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "显示交易结果"},      /*显示交易结果        */
   {"23", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "连接中心"    },      /*连接中心            */
   {"24", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "发送数据"    },      /*发送数据到中心      */
   {"25", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "接收数据"    },      /*从中心接收数据      */
   {"26", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "挂断"        },      /*挂断通讯线路        */
   {"27", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "验证操作密码"},      /*验证操作密码        */
   {"28", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "验证MAC"     },      /*验证MAC             */
   {"29", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "免提拨号"    },      /*免提拨号            */
   {"2A", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "确认交易"    },      /*确认交易是否继续    */
   {"2B", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "更新应用程序"},      /*更新终端应用程序    */
   {"2F", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "显示临时提示"},      /*显示临时操作提示    */
   {"30", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "确定下一指令"},      /*确定下一指令是否执行*/
   {"33", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "读取卡号"    },      /*读取银行卡卡号      */
   {"34", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "上传交易日志"},      /*上传交易日志        */
   {"35", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "上传错误日志"},      /*上传错误日志        */
   {"36", NULL         , 0,0, 1  , 0,0, 0,0, 8  , 0,0,  "终端号"      },      /*取终端号            */
   {"37", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "PC串口数据"  },      /*读取PC串口数据      */
   {"38", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "发送数据"    },      /*发送数据给PC串口    */
   {"39", NULL         , 0,0, 1  , 0,0, 1,1, 100, 0,0,  "签到更新"    },      /*签到更新POS信息     */
   {"3A", NULL         , 0,0, 1  , 0,0, 0,0, 15 , 0,0,  "商户号"      },      /*取商户号            */
   {"3B", NULL         , 0,0, 1  , 0,0, 0,1, 8  , 0,0,  "终端日期"    },      /*取得系统日期        */
   {"3C", NULL         , 0,0, 1  , 0,0, 0,1, 6  , 0,0,  "终端时间"    },      /*取得系统时间        */
   {"3D", NULL         , 0,0, 1  , 0,0, 0,1, 6  , 0,0,  "流水号"      },      /*取得当前流水号      */
   {"3E", NULL         , 0,0, 1  , 0,0, 0,1, 6  , 0,0,  "批次号"      },      /*取得当前批次号      */
   {"3F", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "更新流程"    },      /*更新流程参数        */
   {"40", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "显示日志"    },      /*显示下发的交易日志  */
   {"41", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "存储日志"    },      /*存储下发的交易日志  */
   {"42", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "删除日志"    },      /*删除交易日志        */
   {"43", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "查找日志"    },      /*查找交易日志        */
   {"44", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "记录冲正"    },      /*记录冲正信息        */
   {"45", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "文件名"      },      /*下载的文件名        */
   {"46", NULL         , 0,0, 1  , 0,0, 0,0, 4  , 0,0,  "文件偏移"    },      /*下载的文件偏移      */
   {"47", NULL         , 0,0, 1  , 0,0, 0,0, 0  , 0,0,  "更新文件"    },      /*更新文件            */
   {"48", NULL         , 0,0, 1  , 0,0, 1,0, 0  , 2,1,  "文件名"      },      /*读取文件名          */
   {"49", NULL         , 0,0, 1  , 0,0, 1,0, 0  , 2,1,  "更新下载版本"},      /*更新下载版本信息    */
   {"4A", NULL         , 0,0, 1  , 0,0, 0,0, 1  , 0,0,  "版本类型"    },      /*读取更新版本类型    */
   {"4C", NULL         , 0,0, 1  , 0,0, 1,0, 0  , 2,2,  "一二三磁道信息"},    /*一二三磁道信息      */
   {"4E", NULL         , 0,0, 1  , 0,0, 1,0, 0  , 2,2,  "终端状态信息"},      /*整合终端状态信息*/
   {"4F", NULL         , 0,0, 1  , 0,0, 1,0, 0  , 2,2,  "终端附加签到"},       /*整合终端附加签到报文*/
   {"51", NULL         , 0,0, 1  , 0,0, 1,0, 0  , 2,2,  "终端附加消费"}       /*整合终端附加消费报文*/

};

#endif
