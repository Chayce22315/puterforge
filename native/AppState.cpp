#include "AppState.h"

void AppState::SetStatus(std::string status) {
    status_ = std::move(status);
}

const std::string& AppState::Status() const noexcept {
    return status_;
}

void AppState::SetModels(std::vector<ModelSummary> models) {
    models_ = std::move(models);
}

const std::vector<ModelSummary>& AppState::Models() const noexcept {
    return models_;
}
