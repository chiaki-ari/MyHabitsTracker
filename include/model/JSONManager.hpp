#ifndef JSON_MANAGER_HPP
#define JSON_MANAGER_HPP

#include <string>
#include "json.hpp"

using json = nlohmann::json;

class JSONManager
{
public:
    // ファイル名を指定してインスタンス生成
    // @param file JSONデータを読み書きするファイル名
    explicit JSONManager(const std::string &file)
        : filename_(file) {}

    // JSON読み込みの結果
    static constexpr bool LOAD_SUCCESS = true; ///< 読み込み成功
    static constexpr bool LOAD_ERROR = false;  ///< 読み込み失敗

    // JSON保存の結果
    static constexpr bool SAVE_SUCCESS = true; ///< 保存成功
    static constexpr bool SAVE_ERROR = false;  ///< 保存失敗

    // JSONデータをファイルから読込
    //  @param data 読み込んだJSONデータを格納する変数
    // @return 読み込みが成功した場合LOAD_SUCCESS、失敗した場合LOAD_ERRORを返す
    bool load(json &data);

    /**
     * JSONデータをファイルに保存します。
     * @param data 保存するJSONデータ。
     * @return 保存が成功した場合SAVE_SUCCESS、失敗した場合SAVE_ERRORを返します。
     */
    bool save(const json &data);

private:
    std::string filename_; ///< JSONデータを読み書きするファイル名。
};

#endif // JSON_MANAGER_HPP
