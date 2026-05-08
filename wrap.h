#define SAFE(expr)                                                                                                    \
    [&]() -> decltype(expr) {                                                                                         \
        using RetType = decltype(expr);                                                                               \
        __try {                                                                                                       \
            if constexpr (std::is_void_v<RetType>) {                                                                  \
                (expr);                                                                                               \
                return;                                                                                                \
            } else {                                                                                                  \
                return (expr);                                                                                         \
            }                                                                                                         \
        } __except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER                      \
                                                                   : EXCEPTION_CONTINUE_SEARCH) {                    \
            if constexpr (std::is_same_v<RetType, HRESULT>) {                                                         \
                return D3D_OK;                                                                                         \
            } else if constexpr (std::is_void_v<RetType>) {                                                           \
                return;                                                                                                \
            } else {                                                                                                  \
                return static_cast<RetType>(0);                                                                       \
            }                                                                                                         \
        }                                                                                                             \
    }()