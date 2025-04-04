/********************************************************************************************************
 * @file LogInfoAdapter.java
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
package com.telink.ble.mesh.ui.adapter;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;

import com.telink.ble.mesh.demo.R;
import com.telink.ble.mesh.util.LogInfo;
import com.telink.ble.mesh.util.MeshLogger;

import java.text.SimpleDateFormat;
import java.util.List;
import java.util.Locale;

/**
 * groups in GroupFragment
 * Created by kee on 2017/8/21.
 */

public class LogInfoAdapter extends BaseRecyclerViewAdapter<LogInfoAdapter.ViewHolder> {

    private Context mContext;
    private List<LogInfo> logInfoList;
    private SimpleDateFormat mDateFormat = new SimpleDateFormat("MM-dd HH:mm:ss.SSS", Locale.getDefault());

    public LogInfoAdapter(Context context, List<LogInfo> logInfoList) {
        this.mContext = context;
        this.logInfoList = logInfoList;
    }

    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View itemView = LayoutInflater.from(mContext).inflate(R.layout.item_log_info, parent, false);
        ViewHolder holder = new ViewHolder(itemView);
        holder.tv_name = itemView.findViewById(R.id.tv_log);
        return holder;
    }

    @Override
    public int getItemCount() {
        return logInfoList.size();
    }

    @Override
    public void onBindViewHolder(ViewHolder holder, int position) {
        super.onBindViewHolder(holder, position);
        LogInfo logInfo = logInfoList.get(position);
        if (logInfo != null) {
            String info = mDateFormat.format(logInfo.millis) + "/" + logInfo.tag + " : " + logInfo.logMessage;
            holder.tv_name.setTextColor(mContext.getResources().getColor(getColorResId(logInfo.level)));
            holder.tv_name.setText(info);
        }
    }


    class ViewHolder extends RecyclerView.ViewHolder {
        TextView tv_name;

        public ViewHolder(View itemView) {
            super(itemView);
        }
    }


    private int getColorResId(int level) {
        switch (level) {
            case MeshLogger.LEVEL_VERBOSE:
                return R.color.log_v;
            case MeshLogger.LEVEL_INFO:
                return R.color.log_i;
            case MeshLogger.LEVEL_WARN:
                return R.color.log_w;
            case MeshLogger.LEVEL_ERROR:
                return R.color.log_e;
            case MeshLogger.LEVEL_DEBUG:
            default:
                return R.color.log_d;

        }

    }
}
