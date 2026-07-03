<template>
  <footer class="dtoi-footer">
    <div class="footer-content">
      <p class="copyright">Copyright © 2026 DTOI守夜人团队</p>
      <p class="slogan">守护每一个梦想，创造每一份快乐</p>
      <div class="footer-links">
        <a href="https://github.com/politetrex/lg-dtoi" target="_blank">GitHub</a>
        <span class="separator">|</span>
        <a href="https://www.luogu.com.cn/team/118648" target="_blank">洛谷</a>
      </div>
    </div>
  </footer>
</template>

<style scoped>
.dtoi-footer {
  margin-top: 4rem;
  padding: 2rem 1.5rem;
  border-top: 1px solid var(--vp-c-divider);
  background-color: var(--vp-c-bg-soft);
  text-align: center;
}

.footer-content {
  max-width: 1152px;
  margin: 0 auto;
}

.copyright {
  color: var(--vp-c-text-2);
  font-size: 0.875rem;
  margin: 0 0 0.5rem 0;
}

.slogan {
  color: var(--vp-c-text-3);
  font-size: 0.75rem;
  margin: 0 0 1rem 0;
}

.footer-links {
  display: flex;
  justify-content: center;
  gap: 0.75rem;
  font-size: 0.75rem;
}

.footer-links a {
  color: var(--vp-c-text-2);
  text-decoration: none;
  transition: color 0.2s;
}

.footer-links a:hover {
  color: var(--vp-c-brand);
}

.separator {
  color: var(--vp-c-divider);
}
</style>