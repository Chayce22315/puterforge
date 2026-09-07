#pragma once

#include <string>
#include <vector>

struct ModelSummary {
    std::string id;
    std::string name;
    std::string provider;
};

class AppState {
public:
    void SetStatus(std::string status);
    const std::string& Status() const noexcept;

    void SetModels(std::vector<ModelSummary> models);
    const std::vector<ModelSummary>& Models() const noexcept;

private:
    std::string status_ = "native shell initialized";
    std::vector<ModelSummary> models_;
};
