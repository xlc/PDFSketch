// Copyright...

#ifndef PDFSKETCH_ROOT_VIEW_H__
#define PDFSKETCH_ROOT_VIEW_H__

#include <ppapi/utility/completion_callback_factory.h>
#include <ppapi/cpp/message_loop.h>

#include "view.h"

namespace pdfsketch {

class RootViewDelegate {
 public:
  virtual cairo_t* AllocateCairo() = 0;
  virtual void FlushCairo() = 0;
};

class RootView : public View {
 public:
  RootView() : draw_requested_(false), callback_factory_(this) {}
  virtual void DrawRect(cairo_t* ctx, const Rect& rect);
  virtual void SetNeedsDisplayInRect(const Rect& rect);
  void SetDelegate(RootViewDelegate* delegate) {
    delegate_ = delegate;
  }
  virtual void Resize(const Size& size);
  void HandleDrawRequest(int32_t result);

 private:
  RootViewDelegate* delegate_;
  bool draw_requested_;
  pp::CompletionCallbackFactory<RootView> callback_factory_;
};

}  // namespace pdfsketch

#endif  // PDFSKETCH_ROOT_VIEW_H__