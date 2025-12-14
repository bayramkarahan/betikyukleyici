#!/bin/bash
set -e
export DEBIAN_FRONTEND=noninteractive
PACKAGE_NAME="pardus-yuzyıl"
ARCH="amd64"
BRANCH="master"

TMP_DIR="/tmp/${PACKAGE_NAME}-update"
API_URL="https://api.github.com/repos/bayramkarahan/${PACKAGE_NAME}/commits/${BRANCH}"

mkdir -p "$TMP_DIR"

echo "Paket sistemi kontrol ediliyor..."

# ---- Paket sistemi toparlama (zararsız sıra) ----
dpkg --configure -a || true
apt --fix-broken install -y || true
apt update || true

# ---- Remote sürüm tespiti ----
REMOTE_VERSION=$(curl -s "$API_URL" \
 | grep "\"filename\": \"${PACKAGE_NAME}_.*_${ARCH}.deb\"" -A3 \
 | grep '"status": "added"' -B3 \
 | grep '"filename"' \
 | sed -E "s/.*\"${PACKAGE_NAME}_([^_]+)_${ARCH}.deb\".*/\1/" \
 | head -n1)

if [ -z "$REMOTE_VERSION" ]; then
    echo "Remote sürüm tespit edilemedi."
    exit 0
fi

# ---- Local sürüm ----
LOCAL_VERSION=$(dpkg-query -W -f='${Version}' "$PACKAGE_NAME" 2>/dev/null || echo "none")

echo "Local : $LOCAL_VERSION"
echo "Remote: $REMOTE_VERSION"

# ---- Sürüm karşılaştırma ----
if dpkg --compare-versions "$LOCAL_VERSION" ne "$REMOTE_VERSION"; then
    echo "Sürüm farklı → master sürümüne çekiliyor..."

    DEB_URL="https://github.com/bayramkarahan/${PACKAGE_NAME}/raw/${BRANCH}/${PACKAGE_NAME}_${REMOTE_VERSION}_${ARCH}.deb"
    DEB_FILE="${TMP_DIR}/${PACKAGE_NAME}.deb"

    wget -q -O "$DEB_FILE" "$DEB_URL"

    dpkg --force-all --force-downgrade -i "$DEB_FILE" || true

    # ---- Kurulum sonrası toparlama ----
    apt --fix-broken install -y
    apt autoremove -y

    echo "Sistem ${REMOTE_VERSION} sürümüne getirildi."
else
    echo "Sürüm zaten master ile aynı."
fi
sleep 1
rm -rf ${TMP_DIR}
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/${PACKAGE_NAME}
exit 0

