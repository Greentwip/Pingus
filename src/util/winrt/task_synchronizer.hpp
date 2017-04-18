#ifndef PINGUS_WINRT_TASK_SINCHRONIZER
#define PINGUS_WINRT_TASK_SINCHRONIZER


template <typename TResult>
TResult PerformSynchronously(Windows::Foundation::IAsyncOperation<TResult>^ asyncOp)
{
	Concurrency::event synchronizer;
	Concurrency::task<TResult>(asyncOp).then([&](TResult taskResult) {
		synchronizer.set();
	}, Concurrency::task_continuation_context::use_arbitrary());
	synchronizer.wait();
	return asyncOp->GetResults();
}

#endif