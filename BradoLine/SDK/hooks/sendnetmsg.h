#pragma once

// @credits: https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/public/inetmessage.h
class INetMessage
{
public:
	virtual					~INetMessage() { }
	virtual void			SetNetChannel(void* pNetChannel) = 0;
	virtual void			SetReliable(bool bState) = 0;
	virtual bool			Process() = 0;
	virtual	bool			ReadFromBuffer(uintptr_t& buffer) = 0;
	virtual	bool			WriteToBuffer(uintptr_t& buffer) = 0;
	virtual bool			IsReliable() const = 0;
	virtual int				GetType() const = 0;
	virtual int				GetGroup() const = 0;
	virtual const char* GetName() const = 0;
	virtual void* GetNetChannel() const = 0;
	virtual const char* ToString() const = 0;
	virtual std::size_t		GetSize() const = 0;
};

bool __fastcall hkSendNetMsg(void* thisptr, int edx, INetMessage* pMessage, bool bForceReliable, bool bVoice)
{
	static auto original = minhook::sendnetmsg.GetOriginal<decltype(&hkSendNetMsg)>();

	/*
	 * @note: disable files crc check (sv_pure)
	 * dont send message if it has FileCRCCheck type
	 */
	if (pMessage->GetType() == 14)
		return false;

	/*
	 * @note: fix lag with chocking packets when voice chat is active
	 * check for voicedata group and enable voice stream
	 * @credits: Flaww
	 */
	if (pMessage->GetGroup() == 9)
		bVoice = true;

	return original(thisptr, edx, pMessage, bForceReliable, bVoice);
}