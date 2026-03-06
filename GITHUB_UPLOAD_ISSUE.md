# GitHub上传问题总结

## 问题描述

在将STM32平衡小车项目上传到GitHub仓库时，遇到了以下问题：

1. **GitHub Push Protection 检测到密钥**：
   - 错误信息：`remote: error: GH013: Repository rule violations found for refs/heads/master.`
   - 原因：历史提交中包含了GitHub个人访问令牌
   - 影响：无法将代码推送到GitHub仓库

## 解决方案

### 步骤1：创建新的干净分支

```bash
git checkout --orphan clean-master
```

### 步骤2：添加当前干净的文件

```bash
git add .
```

### 步骤3：创建初始提交

```bash
git commit -m "初始提交：STM32平衡小车项目"
```

### 步骤4：强制推送到远程仓库

```bash
git push -f origin clean-master:master
```

### 步骤5：切换回master分支

```bash
git checkout master
```

## 解决原理

- **创建孤儿分支**：`git checkout --orphan` 创建一个没有历史提交的新分支
- **添加干净文件**：只添加当前目录中的文件，不包含历史提交中的密钥
- **强制推送**：使用 `-f` 参数覆盖远程仓库中的历史，确保远程仓库只包含干净的代码

## 预防措施

1. **不要在代码中硬编码密钥**：使用环境变量或配置文件存储敏感信息
2. **使用 .gitignore 文件**：排除包含敏感信息的文件
3. **定期检查代码**：确保没有意外提交的密钥或敏感信息
4. **使用 GitHub Secrets**：对于CI/CD等场景，使用GitHub的Secrets功能管理敏感信息

## 相关资源

- [GitHub Push Protection 文档](https://docs.github.com/code-security/secret-scanning/working-with-secret-scanning-and-push-protection/working-with-push-protection-from-the-command-line#resolving-a-blocked-push)
- [GitHub 个人访问令牌管理](https://github.com/settings/tokens)