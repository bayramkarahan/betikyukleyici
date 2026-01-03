#!/bin/bash
set -e
export DEBIAN_FRONTEND=noninteractive
PACKAGE_NAME="e-carp"
ARCH="amd64"
BRANCH="master"
GITHUB_USER="bayramkarahan"

TMP_DIR="/tmp/${PACKAGE_NAME}-update"
mkdir -p "$TMP_DIR"

echo "Paket sistemi kontrol ediliyor..."

# ---- Paket sistemi toparlama ----
dpkg --configure -a || true
apt --fix-broken install -y || true
apt update || true

# ---- GitHub contents API ----
CONTENTS_URL="https://api.github.com/repos/bayramkarahan/${PACKAGE_NAME}/contents"

REMOTE_VERSION=$(curl -s "$CONTENTS_URL" \
 | grep "\"name\": \"${PACKAGE_NAME}_" \
 | grep "_${ARCH}.deb\"" \
 | sed -E "s/.*\"${PACKAGE_NAME}_([^_]+)_${ARCH}.deb\".*/\1/" \
 | sort -V \
 | tail -n1)
LOCAL_VERSION=$(dpkg-query -W -f='${Version}' "$PACKAGE_NAME" 2>/dev/null || echo "none")

echo "Local : $LOCAL_VERSION"
echo "Remote: $REMOTE_VERSION"


if dpkg --compare-versions "$LOCAL_VERSION" ne "$REMOTE_VERSION"; then
    echo "Sürüm farklı → master sürümüne çekiliyor..."

    wget -q -O "$TMP_DIR/${PACKAGE_NAME}.deb" \
      "https://github.com/${GITHUB_USER}/${PACKAGE_NAME}/raw/${BRANCH}/${PACKAGE_NAME}_${REMOTE_VERSION}_${ARCH}.deb"

    dpkg --force-all --force-downgrade -i "$TMP_DIR/${PACKAGE_NAME}.deb" || true
    apt --fix-broken install -y
    apt autoremove -y

    echo "Sistem $REMOTE_VERSION sürümüne getirildi."
else
    echo "Sürüm zaten master ile aynı."
fi
rm -rf ${TMP_DIR}
sleep 1
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/${PACKAGE_NAME}
exit 0
#!/bin/bash
set -e
export DEBIAN_FRONTEND=noninteractive
# ---- Paket sistemi toparlama ----
dpkg --configure -a || true
apt install -f -y || true
apt install --fix-missing -y || true
apt --fix-broken install -y || true
packagename="e-carp"
############################################################
wget O /tmp/${packagename}.deb https://github.com/bayramkarahan/e-carp/raw/refs/heads/master/e-carp_1.0.0_amd64.deb
cd /tmp
apt install ./${packagename}.deb --reinstall -y || true
rm -f /tmp/${packagename}.deb || true

apt install -f -y || true
apt --fix-broken install -y || true
apt autoremove -y || true

sleep 1
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/${packagename}
exit 0


