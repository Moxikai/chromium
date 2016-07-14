/*
 * Copyright (C) 2013 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef ClearButtonElement_h
#define ClearButtonElement_h

#include "core/html/HTMLDivElement.h"
#include "wtf/Forward.h"

namespace blink {

class ClearButtonElement final : public HTMLDivElement {
public:
    class ClearButtonOwner : public GarbageCollectedMixin {
    public:
        virtual ~ClearButtonOwner() { }
        virtual void focusAndSelectClearButtonOwner() = 0;
        virtual bool shouldClearButtonRespondToMouseEvents() = 0;
        virtual void clearValue() = 0;
    };

    static ClearButtonElement* create(Document&, ClearButtonOwner&);
    void removeClearButtonOwner() { m_clearButtonOwner = nullptr; }

    DECLARE_VIRTUAL_TRACE();

private:
    ClearButtonElement(Document&, ClearButtonOwner&);
    void detach(const AttachContext& = AttachContext()) override;
    bool isMouseFocusable() const override { return false; }
    void defaultEventHandler(Event*) override;
    bool isClearButtonElement() const override;

    Member<ClearButtonOwner> m_clearButtonOwner;
};

DEFINE_TYPE_CASTS(ClearButtonElement, Element, element, element->isClearButtonElement(), element.isClearButtonElement());

} // namespace blink

#endif // ClearButtonElement_h