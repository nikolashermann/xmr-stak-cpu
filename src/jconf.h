#pragma once
#include <stdlib.h>
#include <string>
#include <vector>

class jconf
{
public:
	static jconf* inst()
	{
		if (oInst == nullptr) oInst = new jconf;
		return oInst;
	};

	bool parse_config(const char* sFilename);

	struct thd_cfg {
		bool bDoubleMode;
		bool bNoPrefetch;
		long long iCpuAff;
	};

	enum slow_mem_cfg {
		always_use,
		no_mlck,
		print_warning,
		never_use,
		unknown_value
	};

	size_t GetThreadCount();
	bool GetThreadConfig(size_t id, thd_cfg &cfg);
	bool NeedsAutoconf();

	slow_mem_cfg GetSlowMemSetting();

	bool GetTlsSetting();
	bool TlsSecureAlgos();
	const char* GetTlsFingerprint();

	const char* GetPoolAddress();
	const char* GetPoolPwd();
	const char* GetWalletAddress();

	uint64_t GetVerboseLevel();
	uint64_t GetAutohashTime();

	const char* GetOutputFile();

	uint64_t GetCallTimeout();
	uint64_t GetNetRetry();
	uint64_t GetGiveUpLimit();

	uint16_t GetHttpdPort();

	bool NiceHashMode();

	bool DaemonMode();

	bool PreferIpv4();

	inline bool HaveHardwareAes() { return bHaveAes; }

	void setCpuThreadsConf(std::vector<thd_cfg> aCpuThreadsConf);

	static void cpuid(uint32_t eax, int32_t ecx, int32_t val[4]);

private:
	jconf();
	static jconf* oInst;

	bool check_cpu_features();

	struct opaque_private;
	opaque_private* prv;

	struct cfg_items {
		std::vector<thd_cfg> aCpuThreadsConf;
		slow_mem_cfg sUseSlowMem;
		bool bNiceHashMode;
		bool bTlsMode;
		bool bTlsSecureAlgo;
		const char* sTlsFingerprint;
		const char* sPoolAddr;
		const char* sWalletAddr;
		const char* sPoolPwd;
		uint64_t iCallTimeout;
		uint64_t iNetRetry;
		uint64_t iGiveUpLimit;
		uint64_t iVerboseLevel;
		uint64_t iAutohashTime;
		bool bDaemonMode;
		const char* sOutputFile;
		uint16_t iHttpdPort;
		bool bPreferIpv4;
	};
	cfg_items* cfgItems = new cfg_items;

	void parseCpuThreadsConf();

	bool bHaveAes;
};
