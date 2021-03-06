///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2016 Edouard Griffiths, F4EXB                                   //
// Copyright (C) 2020 Jon Beniston, M7RCE                                        //
//                                                                               //
// This program is free software; you can redistribute it and/or modify          //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation as version 3 of the License, or                  //
// (at your option) any later version.                                           //
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
#include "packetmodgui.h"
#endif
#include "packetmod.h"
#include "packetmodwebapiadapter.h"
#include "packetmodplugin.h"

const PluginDescriptor PacketModPlugin::m_pluginDescriptor = {
    PacketMod::m_channelId,
    QString("Packet Modulator"),
    QString("4.16.1"),
    QString("(c) Jon Beniston, M7RCE"),
    QString("https://github.com/f4exb/sdrangel"),
    true,
    QString("https://github.com/f4exb/sdrangel")
};

PacketModPlugin::PacketModPlugin(QObject* parent) :
    QObject(parent),
    m_pluginAPI(0)
{
}

const PluginDescriptor& PacketModPlugin::getPluginDescriptor() const
{
    return m_pluginDescriptor;
}

void PacketModPlugin::initPlugin(PluginAPI* pluginAPI)
{
    m_pluginAPI = pluginAPI;

    m_pluginAPI->registerTxChannel(PacketMod::m_channelIdURI, PacketMod::m_channelId, this);
}

#ifdef SERVER_MODE
PluginInstanceGUI* PacketModPlugin::createTxChannelGUI(
        DeviceUISet *deviceUISet,
        BasebandSampleSource *txChannel) const
{
    return 0;
}
#else
PluginInstanceGUI* PacketModPlugin::createTxChannelGUI(DeviceUISet *deviceUISet, BasebandSampleSource *txChannel) const
{
    return PacketModGUI::create(m_pluginAPI, deviceUISet, txChannel);
}
#endif

BasebandSampleSource* PacketModPlugin::createTxChannelBS(DeviceAPI *deviceAPI) const
{
    return new PacketMod(deviceAPI);
}

ChannelAPI* PacketModPlugin::createTxChannelCS(DeviceAPI *deviceAPI) const
{
    return new PacketMod(deviceAPI);
}

ChannelWebAPIAdapter* PacketModPlugin::createChannelWebAPIAdapter() const
{
    return new PacketModWebAPIAdapter();
}
