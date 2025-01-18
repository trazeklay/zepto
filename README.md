# Zepto - YAML-Based Command Executor

Zepto is a lightweight **command execution tool** that allows users to define and execute categorized shell commands from a YAML configuration file.

## 🚀 Features
- Load commands from a structured **YAML file** (`zepto.yaml`).
- Execute commands dynamically using `zepto <category> <command>`.
- **Error handling** for missing categories or commands.
- Simple, fast, and lightweight.

## 🛠️ Installation & Setup

### 1️⃣ **Clone the repository**

```sh
git clone https://github.com/trazeklay/zepto.git
cd zepto
```
---

### 2️⃣ **Install Dependencies**

Zepto uses **libyaml**.

For **Arch linux:**:
```sh
sudo pacman -S yaml
```

For **Ubuntu/Debian**:
```sh
sudo apt install libyaml-dev
```

### 3️⃣ **Build the project**
```sh
make
```

### 4️⃣ **Run Zepto**
```sh
./zepto
```

If `zepto.yaml` does not exist, it will be automatically created.

> NB: If you do not want to enter the ./ each time, copy the `zepto` file into /usr/local/bin directory

---

## 📜 Usage

### **Define commands in `zepto.yaml`**

Edit `zepto.yaml` to define yout categories and commands:
```yaml
scripts:
  db:
    start: docker-compose up -d mongo
    stop: docker-compose stop mongo
  app:
    build: make all
    clean: make clean
  test:
    hi: echo 'Hello, World !'
```

### **Exeecute commands**

Use `zepto <category> <command>` syntax:
```sh
zepto app build
```

💡 **Runs:** `make all`

```sh
zepto test hi
```

💡 **Runs:** `echo 'Hello, World !'`

---

📝 License

This project is licensed under the **MIT License**.

---

👨‍💻 Contributors

- **[Clément TROMPIER](https://github.com/trazeklay)** - Creator & Maintainer

---

⭐️ Support

- Found a bug? **Create an issue** on GitHub.
- Want to contribute ? **Submit a pull request**.