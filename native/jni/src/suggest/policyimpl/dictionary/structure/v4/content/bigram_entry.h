/*
 * Copyright (C) 2013, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LATINIME_BIGRAM_ENTRY_H
#define LATINIME_BIGRAM_ENTRY_H

#include "defines.h"
#include "suggest/policyimpl/dictionary/structure/v4/ver4_dict_constants.h"
#include "suggest/policyimpl/dictionary/utils/historical_info.h"

namespace latinime {

class BigramEntry {
 public:
    BigramEntry(const BigramEntry& bigramEntry)
            : mHasNext(bigramEntry.mHasNext), mProbability(bigramEntry.mProbability),
              mHistoricalInfo(), mTargetTerminalId(bigramEntry.mTargetTerminalId) {}

    // Entry with historical information.
    BigramEntry(const bool hasNext, const int probability, const int targetTerminalId)
            : mHasNext(hasNext), mProbability(probability), mHistoricalInfo(),
              mTargetTerminalId(targetTerminalId) {}

    // Entry with historical information.
    BigramEntry(const bool hasNext, const int probability,
            const HistoricalInfo *const historicalInfo, const int targetTerminalId)
            : mHasNext(hasNext), mProbability(probability), mHistoricalInfo(*historicalInfo),
              mTargetTerminalId(targetTerminalId) {}

    const BigramEntry getInvalidatedEntry() const {
        return updateTargetTerminalIdAndGetEntry(Ver4DictConstants::NOT_A_TERMINAL_ID);
    }

    const BigramEntry updateHasNextAndGetEntry(const bool hasNext) const {
        return BigramEntry(hasNext, mProbability, &mHistoricalInfo, mTargetTerminalId);
    }

    const BigramEntry updateTargetTerminalIdAndGetEntry(const int newTargetTerminalId) const {
        return BigramEntry(mHasNext, mProbability, &mHistoricalInfo, newTargetTerminalId);
    }

    const BigramEntry updateProbabilityAndGetEntry(const int probability) const {
        return BigramEntry(mHasNext, probability, &mHistoricalInfo, mTargetTerminalId);
    }

    const BigramEntry updateHistoricalInfoAndGetEntry(
            const HistoricalInfo *const historicalInfo) const {
        return BigramEntry(mHasNext, mProbability, historicalInfo, mTargetTerminalId);
    }

    bool isValid() const {
        return mTargetTerminalId != Ver4DictConstants::NOT_A_TERMINAL_ID;
    }

    bool hasNext() const {
        return mHasNext;
    }

    int getProbability() const {
        return mProbability;
    }

    const HistoricalInfo *getHistoricalInfo() const {
        return &mHistoricalInfo;
    }

    int getTargetTerminalId() const {
        return mTargetTerminalId;
    }

 private:
    // Copy constructor is public to use this class as a type of return value.
    DISALLOW_DEFAULT_CONSTRUCTOR(BigramEntry);
    DISALLOW_ASSIGNMENT_OPERATOR(BigramEntry);

    const bool mHasNext;
    const int mProbability;
    const HistoricalInfo mHistoricalInfo;
    const int mTargetTerminalId;
};
} // namespace latinime
#endif /* LATINIME_BIGRAM_ENTRY_H */
