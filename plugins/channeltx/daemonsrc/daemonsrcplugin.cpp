///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2018 Edouard Griffiths, F4EXB                                   //
//                                                                               //
// This program is free software; you can redistribute it and/or modify          //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation as version 3 of the License, or                  //
//                                                                               //
// This program is distributed in the hope that it will be useful,               //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License V3 for more details.                               //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with this program. If not, see <http://www.gnu.org/licenses/>.          //
///////////////////////////////////////////////////////////////////////////////////

#include <QtPlugin>
#include "plugin/pluginapi.h"

#ifndef SERVER_MODE
#include "daemonsrcgui.h"
#endif
#include "daemonsrc.h"
#include "daemonsrcplugin.h"

const PluginDescriptor DaemonSrcPlugin::m_pluginDescriptor = {
    QString("Daemon channel source"),
    QString("4.1.0"),
    QString("(c) Edouard Griffiths, F4EXB"),
    QString("https://github.com/f4exb/sdrangel"),
    true,
    QString("https://github.com/f4exb/sdrangel")
};

DaemonSrcPlugin::DaemonSrcPlugin(QObject* parent) :
    QObject(parent),
    m_pluginAPI(0)
{
}

const PluginDescriptor& DaemonSrcPlugin::getPluginDescriptor() const
{
    return m_pluginDescriptor;
}

void DaemonSrcPlugin::initPlugin(PluginAPI* pluginAPI)
{
    m_pluginAPI = pluginAPI;

    // register source
    m_pluginAPI->registerTxChannel(DaemonSrc::m_channelIdURI, DaemonSrc::m_channelId, this);
}

#ifdef SERVER_MODE
PluginInstanceGUI* DaemonSrcPlugin::createTxChannelGUI(
        DeviceUISet *deviceUISet __attribute__((unused)),
        BasebandSampleSource *txChannel __attribute__((unused)))
{
    return 0;
}
#else
PluginInstanceGUI* DaemonSrcPlugin::createTxChannelGUI(DeviceUISet *deviceUISet, BasebandSampleSource *txChannel)
{
    return DaemonSrcGUI::create(m_pluginAPI, deviceUISet, txChannel);
}
#endif

BasebandSampleSource* DaemonSrcPlugin::createTxChannelBS(DeviceSinkAPI *deviceAPI)
{
    return new DaemonSrc(deviceAPI);
}

ChannelSourceAPI* DaemonSrcPlugin::createTxChannelCS(DeviceSinkAPI *deviceAPI)
{
    return new DaemonSrc(deviceAPI);
}



