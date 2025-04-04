/********************************************************************************************************
 * @file PrivateGattProxyGetMessage.java
 *
 * @brief for TLSR chips
 *
 * @author telink
 * @date Sep. 30, 2017
 *
 * @par Copyright (c) 2017, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *******************************************************************************************************/
package com.telink.ble.mesh.core.message.privatebeacon;

import com.telink.ble.mesh.core.message.Opcode;
import com.telink.ble.mesh.core.message.config.ConfigMessage;

/**
 * A PRIVATE_GATT_PROXY_SET message is an acknowledged message used to set the Private GATT Proxy state of a node (see Section 4.2.45).
 * The response to a PRIVATE_GATT_PROXY_SET message is a PRIVATE_GATT_PROXY_STATUS message.
 */
public class PrivateGattProxyGetMessage extends ConfigMessage {

    /**
     * ignore
     *
     * @return
     */
    public PrivateGattProxyGetMessage(int destinationAddress) {
        super(destinationAddress);
    }

    /**
     * ignore
     *
     * @return
     */
    @Override
    public int getOpcode() {
        return Opcode.PRIVATE_GATT_PROXY_GET.value;
    }

    /**
     * ignore
     *
     * @return
     */
    @Override
    public int getResponseOpcode() {
        return Opcode.PRIVATE_GATT_PROXY_STATUS.value;
    }

}
