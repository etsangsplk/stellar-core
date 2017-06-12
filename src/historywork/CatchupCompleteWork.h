// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#pragma once

#include "history/HistoryManager.h"
#include "historywork/CatchupWork.h"

namespace stellar
{

class CatchupCompleteWork : public CatchupWork
{

    typedef std::function<void(asio::error_code const& ec,
                               HistoryManager::CatchupMode mode,
                               LedgerHeaderHistoryEntry const& lastClosed)>
        handler;

    std::shared_ptr<Work> mDownloadLedgersWork;
    std::shared_ptr<Work> mDownloadTransactionsWork;
    std::shared_ptr<Work> mVerifyWork;
    std::shared_ptr<Work> mApplyWork;
    handler mEndHandler;
    virtual uint32_t firstCheckpointSeq() const override;

  public:
    CatchupCompleteWork(Application& app, WorkParent& parent,
                        uint32_t initLedger, bool manualCatchup,
                        handler endHandler);
    std::string getStatus() const override;
    void onReset() override;
    Work::State onSuccess() override;
    void onFailureRaise() override;
};
}
