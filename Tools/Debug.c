
#include "Debug.h"

void CAN_Debug_Send(void)
{
    // TxHeader 用于配置发送帧的信息
    CAN_TxHeaderTypeDef TxHeader;
    // 数据数组
    uint8_t TxData[8] = {0};
    // 发消息时需要用到的邮箱标志
    uint32_t TxMailbox;

    // 示例：标准帧，ID = 0x123
    TxHeader.StdId = 0x123;
    TxHeader.ExtId = 0;                    // 若使用扩展帧则需要修改这里和 IDE 字段
    TxHeader.IDE   = CAN_ID_STD;           // 标准帧
    TxHeader.RTR   = CAN_RTR_DATA;         // 数据帧
    TxHeader.DLC   = 8;                    // 数据长度 0~8 字节
    TxHeader.TransmitGlobalTime = DISABLE; // 一般设为 DISABLE

    // 随意填充一些测试内容，这里写了个 0xAA, 0xBB... 你也可以改成其他值
    TxData[0] = 0xAA;
    TxData[1] = 0xBB;
    TxData[2] = 0xCC;
    TxData[3] = 0xDD;
    TxData[4] = 0x11;
    TxData[5] = 0x22;
    TxData[6] = 0x33;
    TxData[7] = 0x44;

    // 通过 HAL_CAN_AddTxMessage() 函数发送帧
    if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK)
    {
        // 这里可以添加错误处理，比如点灯报警等
        HAL_GPIO_WritePin(GPIOH, GPIO_PIN_11, GPIO_PIN_SET);  // 亮灯
    }
}